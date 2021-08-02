#include "spch.h"
#include "ion.h"
#include <fstream>
#include <nova.h>

namespace Sol {

	const std::filesystem::path base_sln_dir = std::filesystem::absolute(std::filesystem::path(BASE_DIR)).make_preferred();
	const std::filesystem::path Ion::base_path{ base_sln_dir / "Flares"};

	Ion::Ion(const std::string& sln_name) : name(sln_name), path(std::filesystem::absolute(base_path / name)), slnp(path / std::string(name).append(".sln") ) {
		if (!std::filesystem::exists(slnp)) {
			std::filesystem::create_directories(path);
			create_new();
		}
	}

	bool Ion::create_new() {

		#ifdef _WIN64
		static constexpr cstring folders[] = { "Nova", "Sol", "SolarFlare", "build", "bin" };
		for (const auto& folder : folders) {
			// Symlink
			std::system((
				std::string("mklink /J") +
				" \"" + (path / folder).string() + "\"" +
				" \"" + (base_sln_dir / folder).string() + "\""
			).c_str());
		}
		#else
		#error Shortcuts on non windows?
		std::filesystem::create_directory_symlink(base_sln_dir / "Nova", path / "Nova");
		std::filesystem::create_directory_symlink(base_sln_dir / "Sol", path / "Sol");
		#endif // _WIN64

		auto f_sln = std::ofstream(slnp);
		from_template(f_sln, std::ifstream("Sol/vsfile/sln.template"));

		const auto rootvs = base_sln_dir / "Sol/Sol/vsfile/project";
		const auto prj_path = path / name;
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

	void Ion::from_template(std::ofstream& out, std::ifstream f_in) {
		nova_assert(out.is_open(), "Unable to open output file");
		nova_assert(f_in.is_open(), "Unable to open template file");

		std::vector<std::string_view> svs;
		std::string buf(1, 0);
		for (decltype(buf) str; std::getline(f_in, str); ) {
			decltype(buf)::size_type buf_size = 0;
			for (const auto& [sub, func] : sr_table) {
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
			out << str << std::endl;
		}
	}

}