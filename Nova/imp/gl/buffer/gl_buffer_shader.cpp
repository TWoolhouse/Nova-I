#include "npch.h"

#ifdef NOVA_OPENGL
#include "imp/gl/gl_helper.h"
#include <GL/glew.h>
#include <iostream>
#include "gl_buffer_shader.h"
#include "gl_buffer_interface.h"

namespace Nova {

	Star<Buffer::Shader> Buffer::Shader::Create(const Star<Nova::Shader>& shader, const std::string& name, const Shader::Spec& spec) {
		return std::make_shared<OpenGL::BufferShader>(shader, name, spec);
	}

	namespace OpenGL {

		BufferShader::BufferShader(const Star<Nova::Shader>& shader, const std::string& name, const Buffer::Shader::Spec& spec)
			: Buffer::Shader(spec), m_id(GL_NONE) {
			glCreateBuffers(1, &m_id);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);

			const auto size = BufferInterface::scan(shader, name, m_layout);

			glBufferData(GL_SHADER_STORAGE_BUFFER, size, nullptr, GL_STREAM_DRAW);
		}

		void BufferShader::bind(unsigned int slot) {
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, slot, m_id);
		}
		void BufferShader::unbind() {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		}

		void BufferShader::get(const std::string& name, void* const data) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name && "Element Name is not valid");
			glGetNamedBufferSubData(m_id, elm.offset, elm.size, data);
		}

		void BufferShader::get(const std::string& name, void* const data, const unsigned int size, const unsigned int offset) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name && "Element Name is not valid");
			assert(offset < elm.size && "Offset out of range");
			assert((offset + size) <= elm.size && "Offset and Size out of Range");
			glGetNamedBufferSubData(m_id, elm.offset + offset, size, data);
		}

		void BufferShader::set(const std::string& name, const void* data) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name && "Element Name is not valid");
			glNamedBufferSubData(m_id, elm.offset, elm.size, data);
		}

		void BufferShader::set(const std::string& name, const void* data, const unsigned int size, const unsigned int offset) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name && "Element Name is not valid");
			assert(offset < elm.size && "Offset out of range");
			assert((offset + size) <= elm.size && "Offset and Size out of Range");
			glNamedBufferSubData(m_id, elm.offset + offset, size, data);
		}

		void BufferShader::set(const std::string& name, const unsigned int size) {
			auto& elm = m_layout.elements()[name];
			assert(elm.name == name && "Element Name is not valid");
			glNamedBufferData(m_id, size, nullptr, GL_STREAM_DRAW);
			elm.size = size;
		}

		void BufferShader::sync() {
			glMemoryBarrierByRegion(GL_SHADER_STORAGE_BARRIER_BIT);
		}

		BufferShader::~BufferShader() {
			glDeleteBuffers(1, &m_id);
		}

	}

}

#endif // NOVA_OPENGL
