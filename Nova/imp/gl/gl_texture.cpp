#include "npch.h"

#ifdef NOVA_OPENGL
#include "imp/gl/gl_helper.h"
#include <GL/glew.h>
#include <exception>
#include <iostream>
#include "gl_texture.h"
#include "fileio/texture.h"

namespace Nova {

	constexpr GLenum ColourType(const Texture::Colour::Type& colour) {
		switch (colour) {
		case Texture::Colour::Type::RGBA:	return GL_RGBA;
		case Texture::Colour::Type::RGB:	return GL_RGB;
		case Texture::Colour::Type::RGBAW:	return GL_RGBA32F;
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

	Star<Texture2D> Texture2D::Create(const Texture::Properties& properties) {
		return std::make_shared<OpenGL::Texture2D>(properties);
	}
	Star<Texture2D> Texture2D::Create(const unsigned int width, const unsigned int height, const Texture::Properties& properties) {
		return std::make_shared<OpenGL::Texture2D>(width, height, properties);
	}
	Star<Texture2D> Texture2D::Create(const std::string& filename, const Texture::Properties& properties) {
		return std::make_shared<OpenGL::Texture2D>(filename, properties);
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
			m_width = width; m_height = height;
			glTexImage2D(GL_TEXTURE_2D, 0, ColourType(m_colour.format), width, height, 0, ColourType(m_colour.inner), GL_UNSIGNED_BYTE, nullptr);
		}

		Texture2D::Texture2D(const std::string& filename, const Texture::Properties& properties)
			: Texture2D(properties) {
			auto [width, height, data] = FileIO::Texture(filename);
			m_width = width; m_height = height;
			if (data) {
				glTexImage2D(GL_TEXTURE_2D, 0, ColourType(m_colour.format), width, height, 0, ColourType(m_colour.inner), GL_UNSIGNED_BYTE, data);
				// glGenerateMipmap(GL_TEXTURE_2D);
			} else {
				std::cerr << "Failed to load texture" << std::endl;
				throw std::runtime_error("Texture File Not Loaded");
				glDeleteTextures(1, &m_id);
				m_id = GL_NONE;
			}
			FileIO::Texture(data);
		}

		void Texture2D::bind(unsigned int slot) {
			glBindTextureUnit(slot, m_id);
		}

		void Texture2D::unbind(unsigned int slot) {
			glBindTextureUnit(slot, GL_NONE);
		}

		void Texture2D::image(unsigned int slot) {
			glBindImageTexture(slot, m_id, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
		}

		void Texture2D::resize(const unsigned int width, const unsigned int height) {
			nova_gl_bind(GL_TEXTURE_BINDING_2D, m_id);
			glTexImage2D(GL_TEXTURE_2D, 0, ColourType(m_colour.format), width, height, 0, ColourType(m_colour.inner), GL_UNSIGNED_BYTE, nullptr);
			m_width = width; m_height = height;
		}

		void Texture2D::set(const unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int xoff, const unsigned int yoff) {
			assert(xoff <= m_width && "Invalid X-offset");
			assert(yoff <= m_height&& "Invalid Y-offset");
			assert((xoff + width) <= m_width && "Invalid Width");
			assert((yoff + height) <= m_height && "Invalid Height");
			glTextureSubImage2D(m_id, 0, xoff, yoff, width, height, ColourType(m_colour.inner), GL_UNSIGNED_BYTE, data);
		}

		Texture2D::~Texture2D() {
			glDeleteTextures(1, &m_id);
		}

	}

}

#endif // NOVA_OPENGL
