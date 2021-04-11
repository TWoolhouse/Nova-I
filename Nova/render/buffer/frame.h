#pragma once
#include "npch.h"
#include "render/texture.h"

namespace Nova::Buffer {

	class NOVA_API Frame {
	public:
		static Frame* Create();

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual const bool validate() = 0;

		virtual void attach_colour(Texture2D* texture) = 0;
		virtual void attach_depth_stencil(Texture2D* texture) = 0;

		virtual operator bool() = 0;

		virtual ~Frame() {}
	};

}