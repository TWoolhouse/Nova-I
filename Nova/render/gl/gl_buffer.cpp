#include "npch.h"

#ifdef NOVA_OPENGL
#include <GL/glew.h>
#include "gl_buffer.h"

namespace Nova {

	Buffer::Vertex* Buffer::Vertex::Create(const unsigned int size) {
		return new OpenGL::BufferVertex(size);
	}
	Buffer::Vertex* Buffer::Vertex::Create(const unsigned int size, const float* data) {
		return new OpenGL::BufferVertex(size, data);
	}

	Buffer::Index* Buffer::Index::Create(const unsigned int count) {
		return new OpenGL::BufferIndex(count);
	}
	Buffer::Index* Buffer::Index::Create(const unsigned int count, const unsigned int* indices) {
		return new OpenGL::BufferIndex(count, indices);
	}

	namespace OpenGL {

		BufferVertex::BufferVertex() : m_id(GL_NONE) {
			glCreateBuffers(1, &m_id);
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
		}

		BufferVertex::BufferVertex(const unsigned int size) : BufferVertex() {
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		}

		BufferVertex::BufferVertex(const unsigned int size, const float* data) : BufferVertex() {
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

		BufferVertex::~BufferVertex() {
			glDeleteBuffers(1, &m_id);
			m_id = GL_NONE;
		}

		void BufferVertex::bind() {
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
		}

		void BufferVertex::unbind() {
			glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
		}

		void BufferVertex::set(const unsigned int size, const float* data) {
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		}

		BufferIndex::BufferIndex(const unsigned int count) : Buffer::Index(count), m_id(GL_NONE) {
			glCreateBuffers(1, &m_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, nullptr, GL_DYNAMIC_DRAW);
		}

		BufferIndex::BufferIndex(const unsigned int count, const unsigned int* indices) : Buffer::Index(count), m_id(GL_NONE) {
			glCreateBuffers(1, &m_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, indices, GL_STATIC_DRAW);
		}

		BufferIndex::~BufferIndex() {
			glDeleteBuffers(1, &m_id);
			m_id = GL_NONE;
		}

		void BufferIndex::bind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		}

		void BufferIndex::unbind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);
		}
	}

}

#endif // NOVA_OPENGL
