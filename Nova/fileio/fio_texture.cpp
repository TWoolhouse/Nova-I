#include "npch.h"
#include "texture.h"
#include <iostream>
#include <stb_image.h>

namespace Nova::FileIO {

	std::tuple<unsigned int, unsigned int, unsigned char*> Nova::FileIO::Texture(const std::string& filename, const bool& flip) {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(flip);
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 4);
		#ifndef NOVA_RELEASE
		if (!data)
			std::cerr << filename << std::endl;
		nova_assert(data, "Texture Unable to Load");
		#endif // !NOVA_RELEASE
		return { width, height, data };
	}

	void Texture(unsigned char* data) {
		stbi_image_free(data);
	}

}