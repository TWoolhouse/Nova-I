#include "npch.h"

#ifdef NOVA_OPENGL
#include "imp/gl/gl_helper.h"
#include <GL/glew.h>
#include <iostream>
#include "gl_shader.h"
#include "fileio/shader.h"

namespace Nova {

	constexpr GLenum ShaderType(const ShaderSource::Type& type) {
		switch (type) {
		case ShaderSource::Type::Vertex:	return GL_VERTEX_SHADER;
		case ShaderSource::Type::Fragment:	return GL_FRAGMENT_SHADER;
		case ShaderSource::Type::Compute:	return GL_COMPUTE_SHADER;
		case ShaderSource::Type::Geometry:	return GL_GEOMETRY_SHADER;
		default:
			return GL_NONE;
		}
	}

	ShaderSource* ShaderSource::Create(const std::string& filename) {
		return new OpenGL::Shader(filename);
	}
	ShaderSource* ShaderSource::Create(const ShaderSource::Type& type, const std::string& source) {
		return new OpenGL::Shader(type, source);
	}

	Star<Shader> Shader::Create(const std::string& filename) {
		return std::make_shared<OpenGL::ShaderProgram>(filename);
	}
	Star<Shader> Shader::Create(const std::initializer_list<ShaderSource*>& shaders) {
		return std::make_shared<OpenGL::ShaderProgram>(shaders);
	}
	Star<Shader> Shader::Create(const std::initializer_list<ShaderSource*>& shaders, bool save) {
		return std::make_shared<OpenGL::ShaderProgram>(shaders, true);
	}

	Shader::Uniform* Shader::Uniform::Create(Shader* shader) {
		return new OpenGL::UniformUpload(shader);
	}

	Star<ShaderCompute> Nova::ShaderCompute::Create(const std::string& filename, const std::tuple<unsigned int, unsigned int, unsigned int>& work_group) {
		return std::make_shared<OpenGL::ShaderProgramCompute>(filename, work_group);
	}
	Star<ShaderCompute> ShaderCompute::Create(ShaderSource* source, const std::tuple<unsigned int, unsigned int, unsigned int>& work_group) {
		return std::make_shared<OpenGL::ShaderProgramCompute>(source, work_group);
	}
	Star<ShaderCompute> ShaderCompute::Create(ShaderSource* source, bool save, const std::tuple<unsigned int, unsigned int, unsigned int>& work_group) {
		return std::make_shared<OpenGL::ShaderProgramCompute>(source, save, work_group);
	}

	namespace OpenGL {

		Shader::Shader(const std::string& filename) : Nova::ShaderSource(), m_id(GL_NONE) {
			auto [st, src] = FileIO::ShaderSource(filename);
			const bool flag = create_shader(st, src);
			#ifndef NOVA_RELEASE
			if (!flag) {
				std::cerr << "SHADER FILE: " << filename << std::endl;
			}

			#endif // !NOVA_RELEASE
		}

		Shader::Shader(const Nova::ShaderSource::Type& type, const std::string& source) : Nova::ShaderSource(type), m_id(GL_NONE) {
			create_shader(type, source);
		}

		Shader::~Shader() {
			glDeleteShader(m_id);
		}

		bool Shader::create_shader(const Nova::ShaderSource::Type& type, const std::string& source) {
			m_id = glCreateShader(ShaderType(type));

			auto cstr = source.c_str();
			glShaderSource(m_id, 1, &cstr, NULL);
			glCompileShader(m_id);

			#ifndef NOVA_RELEASE
			int success;
			glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
			if (!success) {
				char info[512];
				glGetShaderInfoLog(m_id, 512, NULL, info);
				std::cerr << "SHADER[" << m_id << "] COMPILATION:\n" << info <<
					"SHADER CODE:\n" << source << "//SHADER CODE" << std::endl;
				glDeleteShader(m_id);
				m_id = GL_NONE;
				return false;
			}
			#endif // !NOVA_RELEASE
			return true;
		}

		ShaderProgram::ShaderProgram(const std::initializer_list<Nova::ShaderSource*>& shaders, bool save) : m_id(GL_NONE) {
			create_shader_program(shaders);
		}

		ShaderProgram::ShaderProgram(const std::string& filename) : m_id(GL_NONE) {
			std::vector<Nova::ShaderSource*> shaders;
			auto loader = FileIO::Shader(filename);
			while (++loader) {
				auto [st, src] = *loader;
				shaders.push_back(Nova::ShaderSource::Create(st, src));
			}
			create_shader_program(shaders);
		}

		ShaderProgram::ShaderProgram(const std::initializer_list<Nova::ShaderSource*>& shaders) : ShaderProgram(shaders, true) {
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

		bool ShaderProgram::create_shader_program(const std::vector<Nova::ShaderSource*>& shaders) {
			// Work around dynamic casting inside contructor
			m_uniform_upload = Uniform::Create(static_cast<Nova::Shader*>(this));

			m_id = glCreateProgram();
			for (auto& shader : shaders) {
				glAttachShader(m_id, static_cast<OpenGL::Shader*>(shader)->m_id);
			}
			glLinkProgram(m_id);

			#ifndef NOVA_RELEASE
			int success;
			glGetProgramiv(m_id, GL_LINK_STATUS, &success);
			if (!success) {
				char info[512];
				glGetProgramInfoLog(m_id, 512, NULL, info);
				std::cerr << "SHADER[" << m_id << "] LINKING: ";
				for (const auto& ss : shaders)
					std::cerr << static_cast<OpenGL::Shader*>(ss)->m_id << " ";
				std::cerr << "\n" << info << std::endl;
				return false;
			}
			#endif // !NOVA_RELEASE

			return true;
		}

		UniformUpload::UniformUpload(Nova::Shader* shader) : m_shader_id(dynamic_cast<ShaderProgram*>(shader)->m_id), m_location_cache() {}

		void UniformUpload::Int(const std::string& name, const int value) {
			glProgramUniform1i(m_shader_id, get_location(name), value);
		}
		void UniformUpload::Int(const std::string& name, const unsigned int count, const int* value) {
			glProgramUniform1iv(m_shader_id, get_location(name), count, value);
		}

		void UniformUpload::Float(const std::string& name, const float value) {
			glProgramUniform1f(m_shader_id, get_location(name), value);
		}
		void UniformUpload::Float(const std::string& name, const unsigned int count, const float* value) {
			glProgramUniform1fv(m_shader_id, get_location(name), count, value);
		}

		const int UniformUpload::get_location(const std::string& name) {
			int loc;
			auto search = m_location_cache.find(name);
			if (search == m_location_cache.end()) {
				loc = glGetUniformLocation(m_shader_id, name.c_str());
				m_location_cache[name] = loc;
				return loc;
			}
			return search->second;
		}

		ShaderProgramCompute::ShaderProgramCompute(const std::string& filename, const std::tuple<unsigned int, unsigned int, unsigned int>& work_group)
			: ShaderCompute(work_group), ShaderProgram(filename) {}
		ShaderProgramCompute::ShaderProgramCompute(Nova::ShaderSource* source, const std::tuple<unsigned int, unsigned int, unsigned int>& work_group)
			: ShaderCompute(work_group), ShaderProgram({ source }) {}
		ShaderProgramCompute::ShaderProgramCompute(Nova::ShaderSource* source, bool save, const std::tuple<unsigned int, unsigned int, unsigned int>& work_group)
			: ShaderCompute(work_group), ShaderProgram({ source }, true) {}

		void ShaderProgramCompute::dispatch() {
			nova_gl_bind(GL_CURRENT_PROGRAM, m_id);
			auto [x, y, z] = m_work_group;
			glDispatchCompute(x, y, z);
			glMemoryBarrierByRegion(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT || GL_SHADER_STORAGE_BARRIER_BIT);
		}

		void ShaderProgramCompute::sync() {
			glMemoryBarrierByRegion(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT || GL_SHADER_STORAGE_BARRIER_BIT);
		}

	}

}

#endif // NOVA_OPENGL
