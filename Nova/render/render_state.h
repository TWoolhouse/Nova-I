#pragma once
#include "npch.h"
#include "render.h"
#include "shader.h"
#include "buffer/context.h"
#include "buffer/frame.h"
#include "buffer/uniform.h"
#include "phys/lib.h"

namespace Nova {

	struct NOVA_API Render::RState {
		std::pair<unsigned int, unsigned int> frame_size;
		Star<Shader> shader;
		Buffer::Context* buffer_context;
		Buffer::Frame* framebuffer;
		glm::mat4 matrix{ 1.0f };

		Star<Buffer::Uniform> uniform;

	protected:
		friend class Render;
		RState(Buffer::Frame* fbuff);
		~RState();
	};

}