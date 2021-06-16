#include "npch.h"

#ifdef NOVA_OPENGL
#include <GL/glew.h>
#include <iostream>
#include "gl_buffer_interface.h"
#include "imp/gl/render/gl_shader.h"

#include "gl_buffer_shader.h"
#include "gl_buffer_uniform.h"

namespace Nova::OpenGL {

	template<typename Elm, typename Spec>
	static unsigned int scan_variables(ShaderProgram* shader, const unsigned int& sid, const std::string& name, Spec& spec, GLenum type, GLenum etype) {
		shader->bind();

		// Get Block Index
		GLint var_max_length;
		glGetProgramInterfaceiv(sid, etype, GL_MAX_NAME_LENGTH, &var_max_length);
		if (!var_max_length) var_max_length = 64;
		auto index = glGetProgramResourceIndex(sid, type, name.c_str());

		// Get Number of Variables
		GLenum prop = GL_NUM_ACTIVE_VARIABLES;
		GLint count;
		glGetProgramResourceiv(sid, type, index, 1, &prop, (GLsizei)1, nullptr, &count);

		// Get Variable Index
		auto& elms = spec.elements();
		std::vector<GLint> indices(count);
		prop = GL_ACTIVE_VARIABLES;
		glGetProgramResourceiv(sid, type, index, 1, &prop, (GLsizei)indices.size(), nullptr, indices.data());

		// Get Size of Block
		prop = GL_BUFFER_DATA_SIZE;
		GLint size;
		glGetProgramResourceiv(sid, type, index, 1, &prop, (GLsizei)1, nullptr, &size);

		// Iterate Variables
		prop = GL_OFFSET;
		std::vector<Elm*> selms(elms.size());
		size_t found_count = 0;
		for (size_t i = 0; i < indices.size(); i++) {
			auto& var_index = indices[i];

			// Get Variable Name
			std::vector<GLchar> var_name(var_max_length);
			GLsizei var_length;
			glGetProgramResourceName(
				sid, etype, var_index,
				var_max_length, &var_length, var_name.data());
			std::string var_str = { var_name.data(), var_name.data() + var_length };

			// Remove SubIndex in Name
			auto pos = var_str.find("[");
			if (pos != std::string::npos) {
				var_str = var_str.substr(0, pos);
			}

			// Link to Specifcation
			auto search = elms.find(var_str);
			if (search == elms.end()) continue;
			auto& elm = search->second;
			if (!search->second.size) {
				elm.size = 1;
				selms[found_count++] = &elm;
			}

			// Get Variable Offset
			GLint offset;
			glGetProgramResourceiv(sid, etype, var_index, 1, &prop, (GLsizei)elms.size(), nullptr, (GLint*)(&offset));
			elm.offset = std::min(static_cast<unsigned int>(offset), elm.offset);
		}

		// Sort Variables by offset
		std::sort(selms.begin(), selms.end(), [](const Elm* a, const Elm* b) -> bool {
			return a->offset < b->offset;
		});

		// Calculate and Set Size
		for (size_t i = 0; i < selms.size() - 1; i++) {
			selms[i]->size = selms[i + 1]->offset - selms[i]->offset;
		} selms[selms.size() - 1]->size = size - selms[selms.size() - 1]->offset;

		return size;
	}

	unsigned int BufferInterface::scan(Star<Nova::Shader> shader, const std::string& name, Buffer::Shader::Spec& spec) {
		auto gl_shader = dynamic_cast<ShaderProgram*>(&*shader);
		return scan_variables<Buffer::Shader::Spec::Element>(gl_shader, gl_shader->m_id, name, spec, GL_SHADER_STORAGE_BLOCK, GL_BUFFER_VARIABLE);
	}
	unsigned int BufferInterface::scan(Star<Nova::Shader> shader, const std::string& name, Buffer::Uniform::Spec& spec) {
		auto gl_shader = dynamic_cast<ShaderProgram*>(&*shader);
		return scan_variables<Buffer::Uniform::Spec::Element>(gl_shader, gl_shader->m_id, name, spec, GL_UNIFORM_BLOCK, GL_UNIFORM);
	}

}

#endif // NOVA_OPENGL