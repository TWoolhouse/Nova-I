#pragma once
#include "npch.h"
#include "render/shader.h"
#include <fstream>
#include <sstream>

namespace Nova::FileIO {

	std::pair<ShaderSource::Type, std::string> ShaderSource(const std::string& filename);

	class Shader {
	public:
		Shader(const std::string& filename);

		operator bool() { return current.first != ShaderSource::Type::None; }
		Shader& operator++();
		inline std::pair<ShaderSource::Type, std::string> operator*() { return current; }
	protected:
		std::ifstream file;
		std::pair<ShaderSource::Type, std::string> current;
		ShaderSource::Type next;
	};

}