#pragma once
#include "npch.h"
#include "render/buffer/frame.h"

namespace Nova::OpenGL {

	class BufferFrame : public Buffer::Frame {
	public:
		BufferFrame();
		virtual ~BufferFrame();

		virtual void bind() override;
		virtual void unbind() override;

		virtual const bool validate() override;

		virtual void attach_colour(Nova::Texture2D* texture) override;
		virtual void attach_depth_stencil(Nova::Texture2D* texture) override;

		virtual operator bool() override { return m_success; };
	protected:
		unsigned int m_id;
		bool m_success = false;
	};

}