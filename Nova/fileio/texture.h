#pragma once
#include "render/texture.h"

namespace Nova::FileIO {

	std::tuple<unsigned int, unsigned int, unsigned char*> Texture(const std::string& filename);
	void Texture(unsigned char* data);

}