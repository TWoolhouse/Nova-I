#include "npch.h"
#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace Nova::FileIO {

	ShaderSource::Type get_string_shader_type(const std::string& str) {
		// Must match the Shader::Type layout
		constexpr static size_t types_size = 5;
		static const std::string type_names[types_size] = { "none", "vertex", "fragment", "compute", "geometry" };

		if (str.find("#shader") == std::string::npos)
			return ShaderSource::Type::None;
		for (size_t i = 0; i < types_size; i++) {
			if (str.find(type_names[i]) != std::string::npos)
				return ShaderSource::Type(i);
		}
		return ShaderSource::Type::None;
	}

	std::pair<ShaderSource::Type, std::string> Nova::FileIO::ShaderSource(const std::string& filename) {
		std::ifstream file(filename);
		if (file.is_open()) {
			std::stringstream source;
			std::string line;
			std::getline(file, line);
			auto type = get_string_shader_type(line);
			source << file.rdbuf();
			file.close();
			return { type, source.str() };
		}
		std::cerr << "Shader File Unable to Read: " << filename << std::endl;
		return { ShaderSource::Type::None, "" };
	}

	Shader::Shader(const std::string& filename) : file(filename), current(ShaderSource::Type::None, ""), next(ShaderSource::Type::None) {
		if (!file.is_open()) {
			std::cerr << "Shader File Unable to Read: " << filename << std::endl;
		}
	}

	Shader& Shader::operator++() {
		if (file.is_open()) {
			std::stringstream source;
			std::string line;
			current.first = next;
			auto& type = current.first;

			while (type == ShaderSource::Type::None) {
				if (std::getline(file, line)) {
					type = get_string_shader_type(line);
				} else {
					type = next = ShaderSource::Type::None;
					file.close();
					return *this;
				}
			}

			while (std::getline(file, line)) {
				auto t = get_string_shader_type(line);
				if (t != ShaderSource::Type::None) {
					current.second = source.str();
					source.str(std::string());
					next = t;
					return *this;
				}
				source << line << '\n';
			}
			current.second = source.str();
			next = ShaderSource::Type::None;
			file.close();
		} else {
			next = current.first = ShaderSource::Type::None;
		}
		return *this;
	}

}