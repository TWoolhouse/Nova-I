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

	class ShaderProgram : public virtual Nova::Shader {
		friend class BufferInterface;
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
		virtual void Int(const std::string& name, const unsigned int count, const int* value) override;

		virtual void Float(const std::string& name, const float value) override;
		virtual void Float(const std::string& name, const unsigned int count, const float* value) override;
	protected:
		unsigned int& m_shader_id;
		std::unordered_map<std::string, int> m_location_cache;
		const int get_location(const std::string& name);
	};

	class ShaderProgramCompute : public ShaderCompute, public ShaderProgram {
	public:
		ShaderProgramCompute(const std::string& filename, const std::tuple<unsigned int, unsigned int, unsigned int>& work_group = {1, 1, 1});
		ShaderProgramCompute(ShaderSource* source, const std::tuple<unsigned int, unsigned int, unsigned int>& work_group = { 1, 1, 1 });
		ShaderProgramCompute(ShaderSource* source, bool save, const std::tuple<unsigned int, unsigned int, unsigned int>& work_group = { 1, 1, 1 });
		virtual void dispatch() override;
		virtual void dispatch(const unsigned int x, const unsigned int y, const unsigned int z) override;
		virtual void sync() override;
	};

}