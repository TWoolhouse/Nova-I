#include "npch.h"
#include "stock.h"

namespace Nova::Resource::Stock {

	Asset<Texture2D> Texture::blank{ "nova_blank"_ns, { "Nova/texture/blank.bmp", {} } };
	Asset<Texture2D> Texture::invalid{ "nova_invalid"_ns, { "Nova/texture/invalid.png", { {}, Nova::Texture::Wrap::Type::Repeat, {} } } };
	void Initialise() {
		const unsigned int data = ~0;
		Texture::blank.permanent()->set((const unsigned char*)&data, 1);
	}

}