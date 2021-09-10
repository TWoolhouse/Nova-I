#include "spch.h"
#include "ion.h"
#include <fstream>
#include <nova.h>
#include <chrono>

namespace Sol {

	const std::filesystem::path base_sln_dir = std::filesystem::absolute(std::filesystem::path(BASE_DIR)).make_preferred();
	const std::filesystem::path Ion::base_path{ base_sln_dir / "Flares"};
	const std::filesystem::path sol_dir = base_sln_dir / "Sol";
	const std::filesystem::path flare_dir = sol_dir / "flare";

	Ion::Ion(const std::string& sln_name) : name(sln_name), path(std::filesystem::absolute(base_path / name)), slnp(path / std::string(name).append(".sln") ) {
		if (!std::filesystem::exists(slnp)) {
			create_new();
		}
	}

	void make_symlink_junction(const std::filesystem::path& from, const std::filesystem::path& to) {
		#ifdef OS_WIN
		std::system((
			std::string("mklink /J") +
			" \"" + to.string() + "\"" +
			" \"" + from.string() + "\""
		).c_str());
		#endif // OS_WIN
	}

	bool Ion::create_new() {
		std::filesystem::create_directories(path);
		const auto prj_path = path / name;
		std::filesystem::create_directories(prj_path);

		static constexpr cstring folders[] = { "Nova", "Sol", "build", "bin" };
		for (const auto& folder : folders) {
			make_symlink_junction(base_sln_dir / folder, path / folder);
		}
		make_symlink_junction(flare_dir, prj_path / "flare");

		auto f_sln = std::ofstream(slnp);
		from_template(f_sln, std::ifstream("Sol/vsfile/sln.template"));

		const auto rootvs = sol_dir / "Sol/vsfile/project";
		for (auto& entry : std::filesystem::recursive_directory_iterator(rootvs)) {
			using namespace std::literals;
			const auto& path = std::filesystem::relative(entry.path(), rootvs);
			if (entry.is_directory()) {
				std::filesystem::create_directories(prj_path / path);
				continue;
			}
			auto name = path.filename().string();
			constexpr auto key = ".template"sv;
			const auto& pos = name.rfind(key);
			const auto len = name.length() - key.length();
			if ((pos != std::string::npos) && (pos == len)) {
				const auto fpath = prj_path / path.parent_path() / (this->name + "." + name.substr(0, len));
				auto file = std::ofstream(fpath);
				from_template(file, std::ifstream(entry.path()));
			} else {
				std::filesystem::copy(entry.path(), prj_path / path,std::filesystem::copy_options::update_existing);
			}
		}

		return true;
	}

	template<size_t S>
	std::stringstream& append_file_list(
		const std::filesystem::path& dir, const std::filesystem::path& root,
		const std::string_view& itype, const std::array<cstring, S>& exts,
		std::stringstream& ss
	) {
		using namespace std::string_view_literals;
		for (auto& entry : std::filesystem::recursive_directory_iterator(dir)) {
			const auto& path = std::filesystem::relative(entry.path(), root);
			const auto& ext = path.extension();
			for (const auto& str : exts) {
				if (ext == str) {
					ss << "<Cl"sv << itype << " Include=\""sv << path.string() << "\" />\n"sv;
					break;
				}
			}
		}
		return ss;
	}

	const std::string& Ion::sr_file_compile() const {
		using namespace std::chrono_literals;
		using namespace std::string_view_literals;
		static std::string cache;
		static std::chrono::time_point<std::chrono::steady_clock> cache_time;
		
		if (std::chrono::steady_clock::now() - cache_time < 5s)
			return cache;
		
		std::stringstream ss;
		append_file_list<1>(flare_dir, sol_dir, "Compile"sv, { ".cpp" }, ss);
		const auto ppath = sol_dir / "Sol/vsfile/project";
		append_file_list<1>(ppath, ppath, "Compile"sv, { ".cpp" }, ss);

		cache = ss.str();
		cache_time = std::chrono::steady_clock::now();

		return cache;
	}
	const std::string& Ion::sr_file_include() const {
		using namespace std::chrono_literals;
		using namespace std::string_view_literals;
		static std::string cache;
		static std::chrono::time_point<std::chrono::steady_clock> cache_time;

		if (std::chrono::steady_clock::now() - cache_time < 5s)
			return cache;

		std::stringstream ss;
		append_file_list<1>(flare_dir, sol_dir, "Include"sv, { ".h" }, ss);
		const auto ppath = sol_dir / "Sol/vsfile/project";
		append_file_list<1>(ppath, ppath, "Include"sv, { ".h" }, ss);

		cache = ss.str();
		cache_time = std::chrono::steady_clock::now();

		return cache;
	}

	void Ion::from_template(std::ofstream& out, std::ifstream f_in) {
		nova_assert(out.is_open(), "Unable to open output file");
		nova_assert(f_in.is_open(), "Unable to open template file");

		std::vector<std::string_view> svs;
		std::string buf(1, 0);
		for (decltype(buf) str; std::getline(f_in, str); ) {
			for (const auto& [sub, func] : sr_table) {
				decltype(buf)::size_type buf_size = 0;
				std::string_view sv(str);
				auto idx = sv.find(sub);
				while (idx != std::string_view::npos) {
					auto& rep = (this->*func)();
					svs.emplace_back(sv.substr(0, idx));
					sv.remove_prefix(idx + std::strlen(sub));
					buf_size += idx + svs.emplace_back(rep).size();
					idx = sv.find(sub);
				}
				svs.emplace_back(sv);
				buf_size += sv.size();

				buf.resize(buf_size);
				size_t count = 0;
				for (const auto& v : svs) {
					std::copy(v.cbegin(), v.cend(), buf.begin() + count);
					count += v.size();
				}
				std::swap(str, buf);
				buf.assign(buf.size(), 0);
				svs.clear();
			}
			out << str.c_str() << std::endl;
		}
	}

}