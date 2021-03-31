#pragma once
#include "npch.h"
#include "render/buffer/buffer.h"
#include <GL/glew.h>

namespace Nova::OpenGL {

	class BufferVertex : public Buffer::Vertex {
	public:
		BufferVertex();
		BufferVertex(const unsigned int size);
		BufferVertex(const unsigned int size, const float* data);
		~BufferVertex();

		virtual void bind() override;
		virtual void unbind() override;

		virtual void set(const unsigned int size, const float* data) override;
	private:
		GLuint m_id;
	};

	class BufferIndex : public Buffer::Index {
	public:
		BufferIndex(const unsigned int count);
		BufferIndex(const unsigned int count, const unsigned int* indices);
		~BufferIndex();

		virtual void bind() override;
		virtual void unbind() override;

	private:
		GLuint m_id;
	};

}