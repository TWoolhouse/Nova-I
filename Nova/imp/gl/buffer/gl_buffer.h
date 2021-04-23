#pragma once
#include "npch.h"
#include "render/buffer/buffer.h"

namespace Nova::OpenGL {

	class BufferVertex : public Buffer::Vertex {
	public:
		BufferVertex();
		BufferVertex(const unsigned int size);
		BufferVertex(const unsigned int size, const void* data);
		~BufferVertex();

		virtual void bind() override;
		virtual void unbind() override;

		virtual void set(const unsigned int size, const void* data) override;
	private:
		unsigned int m_id;
	};

	class BufferIndex : public Buffer::Index {
	public:
		BufferIndex(const unsigned int count);
		BufferIndex(const unsigned int count, const unsigned int* indices);
		~BufferIndex();

		virtual void bind() override;
		virtual void unbind() override;

	private:
		unsigned int m_id;
	};

}