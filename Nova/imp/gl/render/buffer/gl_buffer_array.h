#pragma once
#include "render/buffer/context.h"

#ifndef NOVA_RELEASE
#include "render/render.h"
#endif // NOVA_RELEASE

namespace Nova::OpenGL {

	class BufferVertexArray : public Buffer::Context {
		#ifndef NOVA_RELEASE
		friend class Nova::Render::Command;
		#endif // NOVA_RELEASE
	public:
		BufferVertexArray();
		~BufferVertexArray();

		virtual void bind() override;
		virtual void unbind() override;

		virtual void buffer(Buffer::Vertex* buffer, const Buffer::Vertex::Spec& spec) override;
		virtual void buffer(Buffer::Index* buffer) override;
	private:
		unsigned int m_id;
	};

}