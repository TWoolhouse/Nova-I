#pragma once
#include "render/buffer/context.h"

#ifndef NDEBUG
#include "render/render.h"
#endif // NDEBUG

namespace Nova::OpenGL {

	class BufferVertexArray : public Buffer::Context {
		#ifndef NDEBUG
		friend class Nova::Render::Command;
		#endif // NDEBUG
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