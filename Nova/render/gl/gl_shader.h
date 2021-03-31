#pragma once
#include "render/shader.h"

namespace Nova::OpenGL {

	class ShaderProgram;

	class Shader : public Nova::Shader {
		friend ShaderProgram;
	public:
		Shader(const std::string& filename);
		Shader(const Nova::Shader::Type& type, const std::string& source);

		virtual operator bool() override { return m_id; }
		virtual ~Shader() override;
	protected:
		unsigned int m_id;
		bool create_shader(const Nova::Shader::Type& type, const std::string& source);
	};

	class ShaderProgram : public Nova::ShaderPipeline {
	public:
		ShaderProgram(const std::string& filename);
		ShaderProgram(const std::initializer_list<Nova::Shader*>& shaders);
		ShaderProgram(const std::initializer_list<Nova::Shader*>& shaders, bool save);
		virtual void bind() override;
		virtual void unbind() override;

		virtual operator bool() override { return m_id; }
		virtual ~ShaderProgram() override;
	protected:
		unsigned int m_id;
		bool create_shader_program(const std::vector<Nova::Shader*>& shaders);
	};

}