#pragma once
#include "npch.h"
#include "render/buffer/buffer.h"

namespace Nova::OpenGL {

	class BufferVertex : public Buffer::Vertex {
	public:
		BufferVertex();
		BufferVertex(const unsigned int size);
		BufferVertex(const void* data, const unsigned int size);
		~BufferVertex();

		virtual void bind() override;
		virtual void unbind() override;

		virtual void set(const void* data, const unsigned int size) override;
		virtual void set(const void* data, const unsigned int size, const unsigned int offset = 0) override;
		virtual void set(const unsigned int size) override;
	private:
		unsigned int m_id;
	};

	class BufferIndex : public Buffer::Index {
	public:
		BufferIndex(const unsigned int count);
		BufferIndex(const unsigned int* indices, const unsigned int count);
		~BufferIndex();

		virtual void set(const unsigned int* indices, const unsigned int size) override;
		virtual void set(const unsigned int* indices, const unsigned int size, const unsigned int offset) override;
		virtual void set(const unsigned int size) override;

		virtual void bind() override;
		virtual void unbind() override;

	private:
		unsigned int m_id;
	};

}