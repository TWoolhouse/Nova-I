#pragma once
#include "render/buffer_array.h"

namespace Nova::OpenGL {

	class BufferVertexArray : public Buffer::Context {
	public:
		BufferVertexArray();

		virtual void bind() override;
		virtual void unbind() override;

		virtual void buffer(Buffer::Vertex* buffer, const Buffer::VertexSpec& spec) override;
		virtual void buffer(Buffer::Index* buffer) override;
	private:
		unsigned int m_id, m_index = 0;
	};

}