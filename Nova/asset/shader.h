#pragma once
#include "npch.h"
#include "library.h"
#include "render/shader.h"

namespace Nova::Asset {

	class Shader : public Library<Shader, Nova::Shader, std::string> {
	public:
		template<typename ...Args>
		const Star<Nova::Shader> load(const std::string& key, Args... args) {
			return store(key, Nova::Shader::Create(args...));
		}
	};

}