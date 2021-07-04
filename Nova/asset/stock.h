#pragma once
#include "type.h"
#include "render/texture.h"

namespace Nova::Resource::Stock {

	struct NOVA_API Texture {
		static Asset<Texture2D> blank;
		static Asset<Texture2D> invalid;
	};

	void Initialise();

}