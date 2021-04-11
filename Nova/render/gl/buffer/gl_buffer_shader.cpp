#include "npch.h"

#ifdef NOVA_OPENGL
#include "render/gl/gl_bind_helper.h"
#include <GL/glew.h>
#include "gl_buffer_shader.h"

namespace Nova {

	Buffer::Shader* Buffer::Shader::Create(Nova::Shader* shader, const std::string& name, const Shader::Spec& spec) {
		return new OpenGL::BufferShader(shader, name, spec);
	}

	namespace OpenGL {

		BufferShader::BufferShader(Nova::Shader* shader, const std::string& name, const Buffer::Shader::Spec& spec)
			: Buffer::Shader(spec), m_id(GL_NONE) {
			auto gl_shader = static_cast<ShaderProgram*>(shader);
			glCreateBuffers(1, &m_id);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_id);
			gl_shader->bind();
			GLint var_max_length;
			glGetProgramInterfaceiv(gl_shader->m_id, GL_BUFFER_VARIABLE, GL_MAX_NAME_LENGTH, &var_max_length);
			auto index = glGetProgramResourceIndex(gl_shader->m_id, GL_SHADER_STORAGE_BLOCK, name.c_str());

			auto& elms = m_layout.elements();
			std::vector<GLint> indices(elms.size());
			GLenum prop = GL_ACTIVE_VARIABLES;
			glGetProgramResourceiv(gl_shader->m_id, GL_SHADER_STORAGE_BLOCK, index, 1, &prop, (GLsizei)indices.size(), nullptr, indices.data());

			prop = GL_BUFFER_DATA_SIZE;
			GLint size;
			glGetProgramResourceiv(gl_shader->m_id, GL_SHADER_STORAGE_BLOCK, index, 1, &prop, (GLsizei)1, nullptr, &size);

			prop = GL_OFFSET;
			std::vector<Spec::Element*> selms(elms.size());
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
				auto& elm = elms.at(var_str);
				selms[i] = &elm;

				glGetProgramResourceiv(gl_shader->m_id, GL_BUFFER_VARIABLE, var_index, 1, &prop, (GLsizei)elms.size(), nullptr, (GLint*)(&elm.offset));
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

		void BufferShader::set(const std::string& name, const void* data) {
			nova_gl_bind(GL_SHADER_STORAGE_BUFFER_BINDING, m_id);
			auto& elm = m_layout.elements()[name];
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, elm.offset, elm.size, data);
		}
		void BufferShader::set(const std::string& name, const unsigned int size, const void* data) {
			nova_gl_bind(GL_SHADER_STORAGE_BUFFER_BINDING, m_id);
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, m_layout.elements()[name].offset, size, data);
		}

		BufferShader::~BufferShader() {
			glDeleteBuffers(1, &m_id);
		}

	}

}

#endif // NOVA_OPENGL
