#pragma once
#include "npch.h"
#include "render/buffer/shader.h"
#include "imp/gl/render/gl_shader.h"

namespace Nova::OpenGL {

	class BufferShader : public Buffer::Shader {
	public:
		BufferShader(const Star<Nova::Shader>& shader, const std::string& name, const Buffer::Shader::Spec& spec);

		virtual void bind(unsigned int slot=0) override;
		virtual void unbind() override;

		virtual void get(const std::string& name, void* const data) const override;
		virtual void get(const std::string& name, void* const data, const unsigned int size, const unsigned int offset = 0) const override;

		virtual void set(const std::string& name, const void* data) override;
		virtual void set(const std::string& name, const void* data, const unsigned int size, const unsigned int offset = 0) override;
		virtual void set(const std::string& name, const unsigned int size) override;

		virtual void sync() override;

		virtual ~BufferShader() override;
	protected:
		unsigned int m_id;
	};

}