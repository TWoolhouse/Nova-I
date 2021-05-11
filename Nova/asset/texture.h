#pragma once
#include "npch.h"
#include "library.h"
#include "render/texture.h"

namespace Nova::Asset {

	class Texture : public Library<Texture, Texture2D, std::string> {
	public:
		template<typename ...Args>
		const Star<Texture2D> load(const std::string& key, Args... args) {
			return store(key, Texture2D::Create(args...));
		}
	};

}