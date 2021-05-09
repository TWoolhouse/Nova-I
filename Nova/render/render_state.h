#pragma once
#include "npch.h"
#include "shader.h"
#include "buffer/context.h"
#include "buffer/frame.h"
#include "buffer/uniform.h"
#include "phys/maths.h"

namespace Nova {

	struct RenderState {
		std::pair<unsigned int, unsigned int> frame_size;
		Star<Shader> shader;
		Buffer::Context* buffer_context;
		Buffer::Frame* framebuffer;
		Star<Texture2D> blank_texture;
		mlb::mat4 matrix{ 1.0f };

		Star<Buffer::Uniform> uniform;

		static RenderState& Get();

	protected:
		friend class Render;
		RenderState(Buffer::Frame* fbuff);
		~RenderState();
	};

}