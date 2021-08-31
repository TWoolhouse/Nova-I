#pragma once
#include "spch.h"
#include <filesystem>

namespace Sol {

	class Ion {
	protected:
		const static std::filesystem::path base_path;
	public:
		static void gui();
		static void gui_open();
		Ion(const std::string& sln_name);
	protected:
		const std::string& name;
		const std::filesystem::path path, slnp;

		bool create_new();

		void from_template(std::ofstream& out, std::ifstream f_in);

		typedef const std::string& (Ion::*SR)() const;
		const std::string& sr_sln_name() const { return name; }
		const std::string& sr_file_compile() const;
		const std::string& sr_file_include() const;

		static constexpr std::array<std::pair<cstring, SR>, 3> sr_table = {
			std::make_pair("__SLN_NAME__", &sr_sln_name),
			std::make_pair("__FILE_COMPILE__", &sr_file_compile),
			std::make_pair("__FILE_INCLUDE__", &sr_file_include),
		};
	};

}