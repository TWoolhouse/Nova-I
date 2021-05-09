#include "npch.h"

#ifdef NOVA_OPENGL
#include "imp/gl/gl_bind_helper.h"
#include <GL/glew.h>
#include <iostream>
#include "gl_buffer_uniform.h"
#include "gl_buffer_interface.h"

namespace Nova {

	Star<Buffer::Uniform> Buffer::Uniform::Create(const Star<Nova::Shader>& shader, const std::string& name, const Buffer::Uniform::Spec& spec) {
		return std::make_shared<OpenGL::BufferUniform>(shader, name, spec);
	}

	namespace OpenGL {

		BufferUniform::BufferUniform(const Star<Nova::Shader>& shader, const std::string& name, const Buffer::Uniform::Spec& spec)
			: Buffer::Uniform(spec), m_id(GL_NONE) {
			glCreateBuffers(1, &m_id);
			glBindBuffer(GL_UNIFORM_BUFFER, m_id);

			const auto size = BufferInterface::scan(shader, name, m_layout);

			glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STREAM_DRAW);
		}

		void BufferUniform::bind(unsigned int slot) {
			glBindBufferBase(GL_UNIFORM_BUFFER, slot, m_id);
		}
		void BufferUniform::unbind() {
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		void BufferUniform::get(const std::string& name, void* const data) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name && "Element Name is not valid");
			glGetNamedBufferSubData(m_id, elm.offset, elm.size, data);
		}

		void BufferUniform::get(const std::string& name, void* const data, const unsigned int size, const unsigned int offset) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name && "Element Name is not valid");
			assert(offset < elm.size && "Offset out of range");
			assert((offset + size) <= elm.size && "Offset and Size out of Range");
			glGetNamedBufferSubData(m_id, elm.offset + offset, size, data);
		}

		void BufferUniform::set(const std::string& name, const void* data) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name && "Element Name is not valid");
			glNamedBufferSubData(m_id, elm.offset, elm.size, data);
		}

		void BufferUniform::set(const std::string& name, const void* data, const unsigned int size, const unsigned int offset) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name && "Element Name is not valid");
			assert(offset < elm.size && "Offset out of range");
			assert((offset + size) <= elm.size && "Offset and Size out of Range");
			glNamedBufferSubData(m_id, elm.offset + offset, size, data);
		}

		void BufferUniform::set(const std::string& name, const unsigned int size) {
			auto& elm = m_layout.elements()[name];
			assert(elm.name == name && "Element Name is not valid");
			glNamedBufferData(m_id, size, nullptr, GL_STREAM_DRAW);
			elm.size = size;
		}

		BufferUniform::~BufferUniform() {
			glDeleteBuffers(1, &m_id);
		}

	}
}

#endif // NOVA_OPENGL
