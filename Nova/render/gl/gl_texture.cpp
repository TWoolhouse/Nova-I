#include "npch.h"

#ifdef NOVA_OPENGL
#include <GL/glew.h>
#include <iostream>
#include "gl_texture.h"
#include "fileio/stblib/stb_image.h"

namespace Nova {

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

	Texture2D* Texture2D::Create(const Texture::Wrap& wrap, const Texture::Filtering& filter) {
		return new OpenGL::Texture2D(wrap, filter);
	}
	Texture2D* Texture2D::Create(const std::string& filename, const Texture::Wrap& wrap, const Texture::Filtering& filter) {
		return new OpenGL::Texture2D(filename, wrap, filter);
	}

	namespace OpenGL {

		Texture2D::Texture2D(const Texture::Wrap& wrap, const Texture::Filtering& filter) : m_id(GL_NONE) {
			glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapType(wrap.x));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapType(wrap.y));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilteringType(filter.minify));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilteringType(filter.magnify));
		}

		Texture2D::Texture2D(const std::string& filename, const Texture::Wrap& wrap, const Texture::Filtering& filter)
			: Texture2D(wrap, filter) {
			int width, height, channels;
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 4);
			if (data) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				// glGenerateMipmap(GL_TEXTURE_2D);
			} else {
				std::cout << "Failed to load texture" << std::endl;
				glDeleteTextures(1, &m_id);
			}
			stbi_image_free(data);
		}

		void Texture2D::bind() {
			glBindTexture(GL_TEXTURE_2D, m_id);
		}

		void Texture2D::unbind() {
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
		}

		Texture2D::~Texture2D() {
			glDeleteTextures(1, &m_id);
		}

	}

}

#endif // NOVA_OPENGL
