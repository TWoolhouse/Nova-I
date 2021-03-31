#include "npch.h"

#ifdef NOVA_OPENGL
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "gl_shader.h"

namespace Nova {

	GLenum ShaderType(const Shader::Type& type) {
		switch (type) {
		case Shader::Type::Vertex:	return GL_VERTEX_SHADER;
		case Shader::Type::Fragment:	return GL_FRAGMENT_SHADER;
		default:
			return GL_NONE;
		}
	}

	Shader::Type get_string_shader_type(const std::string& str) {
		// Must match the Shader::Type layout
		constexpr static size_t types_size = 3;
		static const std::string type_names[types_size] = { "none", "vertex", "fragment" };

		if (str.find("#shader") == std::string::npos)
			return Shader::Type::None;
		for (size_t i = 0; i < types_size; i++) {
			if (str.find(type_names[i]) != std::string::npos)
				return Shader::Type(i);
		}
		return Shader::Type::None;
	}

	Shader* Shader::Create(const std::string& filename) {
		return new OpenGL::Shader(filename);
	}
	Shader* Shader::Create(const Shader::Type& type, const std::string& source) {
		return new OpenGL::Shader(type, source);
	}

	ShaderPipeline* ShaderPipeline::Create(const std::string& filename) {
		return new OpenGL::ShaderProgram(filename);
	}
	ShaderPipeline* ShaderPipeline::Create(const std::initializer_list<Shader*>& shaders) {
		return new OpenGL::ShaderProgram(shaders);
	}
	ShaderPipeline* ShaderPipeline::Create(const std::initializer_list<Shader*>& shaders, bool save) {
		return new OpenGL::ShaderProgram(shaders, true);
	}

	namespace OpenGL {

		Shader::Shader(const std::string& filename) : Nova::Shader(), m_id(GL_NONE) {
			std::ifstream file(filename);
			if (file.is_open()) {
				std::stringstream source;
				std::string line;
				std::getline(file, line);
				auto type = get_string_shader_type(line);
				source << file.rdbuf();
				file.close();
				create_shader(type, source.str());
			} else { // Not Open
				create_shader(Nova::Shader::Type::None, "");
			}
		}

		Shader::Shader(const Nova::Shader::Type& type, const std::string& source) : Nova::Shader(), m_id(GL_NONE) {
			create_shader(type, source);
		}

		Shader::~Shader() {
			glDeleteShader(m_id);
		}

		bool Shader::create_shader(const Nova::Shader::Type& type, const std::string& source) {
			m_id = glCreateShader(ShaderType(type));

			auto cstr = source.c_str();
			glShaderSource(m_id, 1, &cstr, NULL);
			glCompileShader(m_id);

			int success;
			glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
			if (!success) {
				char info[512];
				glGetShaderInfoLog(m_id, 512, NULL, info);
				std::cout << "ERROR: Shader Compliation\n" << info << std::endl;
				glDeleteShader(m_id);
				m_id = GL_NONE;
				return false;
			}
			return true;
		}

		ShaderProgram::ShaderProgram(const std::initializer_list<Nova::Shader*>& shaders, bool save) : m_id(GL_NONE) {
			create_shader_program(shaders);
		}

		ShaderProgram::ShaderProgram(const std::string& filename) : m_id(GL_NONE) {
			std::vector<Nova::Shader*> shaders;

			std::ifstream file(filename);
			if (file.is_open()) {
				std::stringstream source;
				std::string line;
				auto type = Nova::Shader::Type::None;

				while (type == Nova::Shader::Type::None) {
					std::getline(file, line);
					type = get_string_shader_type(line);
				}

				while (std::getline(file, line)) {
					auto t = get_string_shader_type(line);
					if (t != Nova::Shader::Type::None) {
						type = t;
						shaders.push_back(Nova::Shader::Create(type, source.str()));
						source.clear();
						continue;
					}
				}
				shaders.push_back(Nova::Shader::Create(type, source.str()));
				file.close();
			} else { // Not Open
				// Probably Error?
			}
			create_shader_program(shaders);
		}

		ShaderProgram::ShaderProgram(const std::initializer_list<Nova::Shader*>& shaders) : ShaderProgram(shaders, true) {
			for (auto& shader : shaders) {
				delete shader;
			}
		}

		void ShaderProgram::bind() {
			glUseProgram(m_id);
		}

		void ShaderProgram::unbind() {
			glUseProgram(GL_NONE);
		}

		ShaderProgram::~ShaderProgram() {
			glDeleteProgram(m_id);
		}

		bool ShaderProgram::create_shader_program(const std::vector<Nova::Shader*>& shaders) {
			m_id = glCreateProgram();
			for (auto& shader : shaders) {
				glAttachShader(m_id, static_cast<Shader*>(shader)->m_id);
			}
			glLinkProgram(m_id);
			return true;
		}

	}

}

#endif // NOVA_OPENGL
