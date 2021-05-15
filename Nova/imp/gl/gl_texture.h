#pragma once
#include "npch.h"
#include "render/texture.h"

namespace Nova::OpenGL {

	class Texture2D : public Nova::Texture2D {
		friend class BufferFrame;
	public:
		Texture2D(const Texture::Properties& properties);
		Texture2D(const unsigned int width, const unsigned int height, const Texture::Properties& properties);
		Texture2D(const std::string& filename, const Texture::Properties& properties);

		virtual void bind(unsigned int slot = 0) override;
		virtual void unbind(unsigned int slot = 0) override;
		virtual void image(unsigned int slot = 0) override;

		virtual void resize(const unsigned int width, const unsigned int height) override;
		virtual void set(const unsigned char* data, const unsigned int width, const unsigned int height = 1, const unsigned int xoff = 0, const unsigned int yoff = 0) override;

		virtual operator bool() override { return m_id; }

		virtual const unsigned int& id() const { return m_id; };

		virtual ~Texture2D() override;
	protected:
		unsigned int m_id;
		Texture::Colour m_colour;
	};

}