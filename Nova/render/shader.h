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
		static Shader* Create(const std::string& filename);
		static Shader* Create(const std::initializer_list<ShaderSource*>& shaders);
		static Shader* Create(const std::initializer_list<ShaderSource*>& shaders, bool save);

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual operator bool() = 0;
		virtual ~Shader() {};
	};

}