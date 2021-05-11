#pragma once
#include "npch.h"
#include "library.h"
#include "render/buffer/uniform.h"

namespace Nova::Asset {

	class Uniform : public Library<Uniform, Buffer::Uniform, std::string> {
	public:
		template<typename ...Args>
		const Star<Buffer::Uniform> load(const std::string& key, Args... args) {
			return store(key, Buffer::Uniform::Create(args...));
		}
	};

}