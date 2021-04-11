#pragma once
#include "render/shader.h"

namespace Nova::OpenGL {

	class ShaderProgram;

	class Shader : public Nova::ShaderSource {
		friend ShaderProgram;
	public:
		Shader(const std::string& filename);
		Shader(const Nova::ShaderSource::Type& type, const std::string& source);

		virtual operator bool() override { return m_id; }
		virtual ~Shader() override;
	protected:
		unsigned int m_id;
		bool create_shader(const Nova::ShaderSource::Type& type, const std::string& source);
	};

	class UniformUpload;

	class ShaderProgram : public Nova::Shader {
		friend class BufferShader;
		friend UniformUpload;
	public:
		ShaderProgram(const std::string& filename);
		ShaderProgram(const std::initializer_list<Nova::ShaderSource*>& shaders);
		ShaderProgram(const std::initializer_list<Nova::ShaderSource*>& shaders, bool save);
		virtual void bind() override;
		virtual void unbind() override;

		virtual operator bool() override { return m_id; }
		virtual ~ShaderProgram() override;
	protected:
		unsigned int m_id;
		bool create_shader_program(const std::vector<Nova::ShaderSource*>& shaders);
	};

	class UniformUpload : public Nova::Shader::Uniform {
	public:
		UniformUpload(Nova::Shader* shader);
		virtual ~UniformUpload() override {};

		virtual void Int(const std::string& name, const int value) override;
		virtual void Float(const std::string& name, const float value) override;
	protected:
		unsigned int& m_shader_id;
		std::unordered_map<std::string, int> m_location_cache;
		const int get_location(const std::string& name);
	};

	class ShaderProgramCompute : public ShaderCompute, public ShaderProgram {
		virtual void dispatch() override;
	};

}