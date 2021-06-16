#pragma once
#include "npch.h"
#include "render/buffer/uniform.h"

namespace Nova::OpenGL {

	class BufferUniform : public Buffer::Uniform {
	public:
		BufferUniform(const Star<Nova::Shader>& shader, const std::string& name, const Buffer::Uniform::Spec& spec);

		virtual void bind(unsigned int slot = 0) override;
		virtual void unbind() override;

		virtual void get(const std::string& name, void* const data) override;
		virtual void get(const std::string& name, void* const data, const unsigned int size, const unsigned int offset = 0) override;

		virtual void set(const std::string& name, const void* data) override;
		virtual void set(const std::string& name, const void* data, const unsigned int size, const unsigned int offset = 0) override;
		virtual void set(const std::string& name, const unsigned int size) override;

		virtual ~BufferUniform() override;
	protected:
		unsigned int m_id;
	};

}