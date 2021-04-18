#include "npch.h"
#include "texture.h"
#include <iostream>
#include <stb_image.h>

namespace Nova::FileIO {

	std::tuple<unsigned int, unsigned int, unsigned char*> Nova::FileIO::Texture(const std::string& filename) {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 4);
		return { width, height, data };
	}

	void Texture(unsigned char* data) {
		stbi_image_free(data);
	}

}