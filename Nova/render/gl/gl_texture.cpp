#include "npch.h"

#ifdef NOVA_OPENGL
#include <GL/glew.h>
#include <iostream>
#include "gl_texture.h"
#include "fileio/stblib/stb_image.h"

namespace Nova {

	constexpr GLenum ColourType(const Texture::Colour::Type& colour) {
		switch (colour) {
		case Texture::Colour::Type::RGBA:	return GL_RGBA;
		case Texture::Colour::Type::RGB:	return GL_RGB;
		default:
			return GL_RGBA;
		}
	}
	constexpr GLenum WrapType(const Texture::Wrap::Type& wrap) {
		switch (wrap) {
		case Texture::Wrap::Type::Repeat:	return GL_REPEAT;
		case Texture::Wrap::Type::Mirror:	return GL_MIRRORED_REPEAT;
		case Texture::Wrap::Type::ClampBorder:	return GL_CLAMP_TO_BORDER;
		case Texture::Wrap::Type::ClampEdge:	return GL_CLAMP_TO_EDGE;
		default:
			return GL_REPEAT;
		}
	}
	constexpr GLenum FilteringType(const Texture::Filtering::Type& filter) {
		switch (filter) {
		case Texture::Filtering::Type::Linear:	return GL_LINEAR;
		case Texture::Filtering::Type::Nearest:	return GL_NEAREST;
		default:
			return GL_LINEAR;
		}
	}

	Texture2D* Texture2D::Create(const Texture::Properties& properties) {
		return new OpenGL::Texture2D(properties);
	}
	Texture2D* Texture2D::Create(const unsigned int width, const unsigned int height, const Texture::Properties& properties) {
		return new OpenGL::Texture2D(width, height, properties);
	}
	Texture2D* Texture2D::Create(const std::string& filename, const Texture::Properties& properties) {
		return new OpenGL::Texture2D(filename, properties);
	}

	namespace OpenGL {

		Texture2D::Texture2D(const Texture::Properties& properties) : m_id(GL_NONE), m_colour(properties.colour) {
			glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapType(properties.wrap.x));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapType(properties.wrap.y));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilteringType(properties.filter.minify));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilteringType(properties.filter.magnify));
		}

		Texture2D::Texture2D(const unsigned int width, const unsigned int height, const Texture::Properties& properties)
			: Texture2D(properties) {
			glTexImage2D(GL_TEXTURE_2D, 0, ColourType(m_colour.format), width, height, 0, ColourType(m_colour.inner), GL_UNSIGNED_BYTE, nullptr);
		}

		Texture2D::Texture2D(const std::string& filename, const Texture::Properties& properties)
			: Texture2D(properties) {
			int width, height, channels;
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 4);
			if (data) {
				glTexImage2D(GL_TEXTURE_2D, 0, ColourType(m_colour.format), width, height, 0, ColourType(m_colour.inner), GL_UNSIGNED_BYTE, data);
				// glGenerateMipmap(GL_TEXTURE_2D);
			} else {
				std::cerr << "Failed to load texture" << std::endl;
				glDeleteTextures(1, &m_id);
			}
			stbi_image_free(data);
		}

		void Texture2D::bind(unsigned int slot) {
			glBindTextureUnit(slot, m_id);
		}

		void Texture2D::unbind(unsigned int slot) {
			glBindTextureUnit(slot, GL_NONE);
		}

		Texture2D::~Texture2D() {
			glDeleteTextures(1, &m_id);
		}

	}

}

#endif // NOVA_OPENGL
