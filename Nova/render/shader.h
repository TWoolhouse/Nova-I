#pragma once
#include "npch.h"

namespace Nova {

	class NOVA_API Shader {
	public:
		enum class Type: unsigned char {
			None = 0,
			Vertex, Fragment
		};

		static Shader* Create(const std::string& filename);
		static Shader* Create(const Type& type, const std::string& source);

		Shader(const Type& type=Type::None) : m_type(type) {}

		const Type& type() const { return m_type; }

		virtual operator bool() = 0;
		virtual ~Shader() {};
	protected:
		Type m_type;
	};

	class NOVA_API ShaderPipeline {
	public:
		static ShaderPipeline* Create(const std::string& filename);
		static ShaderPipeline* Create(const std::initializer_list<Shader*>& shaders);
		static ShaderPipeline* Create(const std::initializer_list<Shader*>& shaders, bool save);

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual operator bool() = 0;
		virtual ~ShaderPipeline() {};
	};

}