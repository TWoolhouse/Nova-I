#pragma once
#include "npch.h"

namespace Nova {

	class NOVA_API ShaderSource {
	public:
		enum class Type: unsigned char {
			None = 0,
			Vertex, Fragment, Compute,
		};

		static ShaderSource* Create(const std::string& filename);
		static ShaderSource* Create(const Type& type, const std::string& source);

		ShaderSource(const Type& type=Type::None) : m_type(type) {}

		const Type& type() const { return m_type; }

		virtual operator bool() = 0;
		virtual ~ShaderSource() {};
	protected:
		Type m_type;
	};

	class NOVA_API Shader {
	public:
		class NOVA_API Uniform {
		public:
			static Uniform* Create(Shader* shader);
			virtual ~Uniform() {};

			virtual void Int(const std::string& name, const int value) = 0;
			virtual void Float(const std::string& name, const float value) = 0;
		};

		static Shader* Create(const std::string& filename);
		static Shader* Create(const std::initializer_list<ShaderSource*>& shaders);
		static Shader* Create(const std::initializer_list<ShaderSource*>& shaders, bool save);

		Shader() : m_uniform_upload() {}

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual operator bool() = 0;
		virtual ~Shader() {
			delete m_uniform_upload;
		};

		Uniform* Upload() const { return m_uniform_upload; }

	protected:
		Uniform* m_uniform_upload;
	};

	class NOVA_API ShaderCompute : public virtual Shader {
		// Add safety so only compute shaders can be added
		// require compute shader source
	public:
		static ShaderCompute* Create(const std::string& filename);
		static ShaderCompute* Create(ShaderSource* source);
		static ShaderCompute* Create(ShaderSource* source, bool save);

		ShaderCompute(const std::tuple<unsigned int, unsigned int, unsigned int>& work_group = {1, 1, 1}) : Shader(), m_work_group(work_group) {}

		virtual void dispatch() = 0;
	protected:
		std::tuple<unsigned int, unsigned int, unsigned int> m_work_group;
	};

}