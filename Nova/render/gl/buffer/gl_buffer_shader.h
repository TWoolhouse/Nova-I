#pragma once
#include "npch.h"
#include "render/buffer/shader.h"
#include "render/gl/gl_shader.h"

namespace Nova::OpenGL {

	class BufferShader : public Buffer::Shader {
	public:
		BufferShader(Nova::Shader* shader, const std::string& name, const Buffer::Shader::Spec& spec);

		virtual void bind(unsigned int slot=0) override;
		virtual void unbind() override;

		virtual void set(const std::string& name, const void* data) override;
		virtual void set(const std::string& name, const unsigned int size, const void* data) override;

		virtual ~BufferShader() override;
	protected:
		unsigned int m_id;
	};

}