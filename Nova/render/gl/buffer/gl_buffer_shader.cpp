#include "npch.h"

#ifdef NOVA_OPENGL
#include "render/gl/gl_bind_helper.h"
#include <GL/glew.h>
#include <iostream>
#include "gl_buffer_shader.h"

namespace Nova {

	Buffer::Shader* Buffer::Shader::Create(Nova::Shader* shader, const std::string& name, const Shader::Spec& spec) {
		return new OpenGL::BufferShader(shader, name, spec);
	}

	namespace OpenGL {

		BufferShader::BufferShader(Nova::Shader* shader, const std::string& name, const Buffer::Shader::Spec& spec)
			: Buffer::Shader(spec), m_id(GL_NONE) {
			auto gl_shader = dynamic_cast<ShaderProgram*>(shader);
			glCreateBuffers(1, &m_id);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
			gl_shader->bind();
			GLint var_max_length;
			glGetProgramInterfaceiv(gl_shader->m_id, GL_BUFFER_VARIABLE, GL_MAX_NAME_LENGTH, &var_max_length);
			auto index = glGetProgramResourceIndex(gl_shader->m_id, GL_SHADER_STORAGE_BLOCK, name.c_str());

			GLenum prop = GL_NUM_ACTIVE_VARIABLES;
			GLint count;
			glGetProgramResourceiv(gl_shader->m_id, GL_SHADER_STORAGE_BLOCK, index, 1, &prop, (GLsizei)1, nullptr, &count);

			auto& elms = m_layout.elements();
			std::vector<GLint> indices(count);
			prop = GL_ACTIVE_VARIABLES;
			glGetProgramResourceiv(gl_shader->m_id, GL_SHADER_STORAGE_BLOCK, index, 1, &prop, (GLsizei)indices.size(), nullptr, indices.data());

			prop = GL_BUFFER_DATA_SIZE;
			GLint size;
			glGetProgramResourceiv(gl_shader->m_id, GL_SHADER_STORAGE_BLOCK, index, 1, &prop, (GLsizei)1, nullptr, &size);

			prop = GL_OFFSET;
			std::vector<Spec::Element*> selms(elms.size());
			size_t found_count = 0;
			for (size_t i = 0; i < indices.size(); i++) {
				auto& var_index = indices[i];

				std::vector<GLchar> var_name(var_max_length);
				GLsizei var_length;
				glGetProgramResourceName(
					gl_shader->m_id, GL_BUFFER_VARIABLE, var_index,
					var_max_length, &var_length, var_name.data());
				std::string var_str = { var_name.data(), var_name.data() + var_length };
				auto pos = var_str.find("[");
				if (pos != std::string::npos) {
					var_str = var_str.substr(0, pos);
				}
				auto search = elms.find(var_str);
				if (search == elms.end()) continue;
				auto& elm = search->second;
				if (!search->second.size) {
					elm.size = 1;
					selms[found_count++] = &elm;
				}

				GLint offset;
				glGetProgramResourceiv(gl_shader->m_id, GL_BUFFER_VARIABLE, var_index, 1, &prop, (GLsizei)elms.size(), nullptr, (GLint*)(&offset));
				elm.offset = std::min(static_cast<unsigned int>(offset), elm.offset);
			}

			std::sort(selms.begin(), selms.end(), [](const Spec::Element* a, const Spec::Element* b) -> bool {
				return a->offset < b->offset;
			});
			for (size_t i = 0; i < selms.size()-1; i++) {
				selms[i]->size = selms[i + 1]->offset - selms[i]->offset;
			} selms[selms.size() - 1]->size = size - selms[selms.size() - 1]->offset;

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
			assert(elm.name == name, "Element Name is not valid");
			glGetNamedBufferSubData(m_id, elm.offset, elm.size, data);
		}

		void BufferShader::get(const std::string& name, const unsigned int size, void* const data) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name, "Element Name is not valid");
			glGetNamedBufferSubData(m_id, elm.offset, size, data);
		}

		void BufferShader::get(const std::string& name, const unsigned int offset, const unsigned int size, void* const data) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name, "Element Name is not valid");
			assert(offset < elm.size, "Offset out of range");
			assert((offset + size) <= elm.size, "Offset and Size out of Range");
			glGetNamedBufferSubData(m_id, elm.offset + offset, size, data);
		}

		void BufferShader::set(const std::string& name, const void* data) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name, "Element Name is not valid");
			glNamedBufferSubData(m_id, elm.offset, elm.size, data);
		}
		void BufferShader::set(const std::string& name, const unsigned int size, const void* data) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name, "Element Name is not valid");
			glNamedBufferSubData(m_id, elm.offset, size, data);
		}

		void BufferShader::set(const std::string& name, const unsigned int offset, const unsigned int size, void* const data) {
			const auto& elm = m_layout.elements()[name];
			assert(elm.name == name, "Element Name is not valid");
			assert(offset < elm.size, "Offset out of range");
			assert((offset + size) <= elm.size, "Offset and Size out of Range");
			glNamedBufferSubData(m_id, elm.offset + offset, size, data);
		}

		void BufferShader::set(const std::string& name, const unsigned int size) {
			auto& elm = m_layout.elements()[name];
			assert(elm.name == name, "Element Name is not valid");
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
