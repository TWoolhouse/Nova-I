#pragma once
#include "npch.h"
#include "render/texture.h"

namespace Nova::OpenGL {

	class Texture2D : public Nova::Texture2D {
	public:
		Texture2D(const Texture::Wrap& wrap, const Texture::Filtering& filter);
		Texture2D(const std::string& filename, const Texture::Wrap& wrap, const Texture::Filtering& filter);

		virtual void bind() override;
		virtual void unbind() override;

		virtual operator bool() override { return m_id; }

		virtual ~Texture2D() override;
	protected:
		unsigned int m_id;
	};

}