#include "npch.h"

#ifdef NOVA_OPENGL
#include <GL/glew.h>
#include "gl_buffer_array.h"

namespace Nova {

	Buffer::Context* Buffer::Context::Create() {
		return new OpenGL::BufferVertexArray();
	}

	namespace OpenGL {

		GLenum TypeConvert(const Buffer::Type& type) {
			switch (type) {
			case Buffer::Type::Float:	return GL_FLOAT;
			case Buffer::Type::Float2:	return GL_FLOAT;
			case Buffer::Type::Float3:	return GL_FLOAT;
			case Buffer::Type::Float4:	return GL_FLOAT;
			case Buffer::Type::Int:	return GL_INT;
			case Buffer::Type::Int2:	return GL_INT;
			case Buffer::Type::Int3:	return GL_INT;
			case Buffer::Type::Int4:	return GL_INT;
			case Buffer::Type::UInt:	return GL_UNSIGNED_INT;
			case Buffer::Type::UInt2:	return GL_UNSIGNED_INT;
			case Buffer::Type::UInt3:	return GL_UNSIGNED_INT;
			case Buffer::Type::UInt4:	return GL_UNSIGNED_INT;
			case Buffer::Type::Double:	return GL_DOUBLE;
			case Buffer::Type::Double2:	return GL_DOUBLE;
			case Buffer::Type::Double3:	return GL_DOUBLE;
			case Buffer::Type::Double4:	return GL_DOUBLE;
			case Buffer::Type::Mat2:	return GL_FLOAT;
			case Buffer::Type::Mat3:	return GL_FLOAT;
			case Buffer::Type::Mat4:	return GL_FLOAT;
			case Buffer::Type::Bool:	return GL_BOOL;
			case Buffer::Type::None:	return GL_NONE;
			default:
				return GL_NONE;
			}
		}

		BufferVertexArray::BufferVertexArray() : m_id(GL_NONE) {
			glCreateVertexArrays(1, &m_id);
			glBindVertexArray(m_id);
		}

		BufferVertexArray::~BufferVertexArray() {
			glDeleteVertexArrays(1, &m_id);
		}

		void BufferVertexArray::bind() {
			glBindVertexArray(m_id);
		}

		void BufferVertexArray::unbind() {
			glBindVertexArray(GL_NONE);
		}

		void BufferVertexArray::buffer(Buffer::Vertex* buffer, const Buffer::VertexSpec& spec) {
			glBindVertexArray(m_id);
			buffer->bind();
			for (auto& elm : spec) {
				glEnableVertexAttribArray(m_index);
				glVertexAttribPointer(m_index++, elm.count, TypeConvert(elm.type), elm.normalise, spec.stride(), (void*)elm.offset);
			}
		}

		void BufferVertexArray::buffer(Buffer::Index* buffer) {
			glBindVertexArray(m_id);
			buffer->bind();
			m_index_buffer = buffer;
		}

	}

}

#endif // NOVA_OPENGL
