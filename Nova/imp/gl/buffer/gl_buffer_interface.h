#pragma once
#include "npch.h"
#include "render/shader.h"
#include "render/buffer/shader.h"
#include "render/buffer/uniform.h"

namespace Nova::OpenGL {

	class BufferInterface {
	public:
		static unsigned int scan(Star<Nova::Shader> shader, const std::string& name, Buffer::Shader::Spec& spec);
		static unsigned int scan(Star<Nova::Shader> shader, const std::string& name, Buffer::Uniform::Spec& spec);
	};

}