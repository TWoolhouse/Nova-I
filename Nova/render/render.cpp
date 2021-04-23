#include "npch.h"
#include "render.h"
#include "command.h"
#include "buffer/context.h"
#include "buffer/frame.h"
#include "shader.h"
#include "core/application.h"

namespace FrameOutput {
	// 4K
	//constexpr unsigned int width = 3840;
	//constexpr unsigned int height = 2160;

	// 1080
	constexpr unsigned int width = 1920;
	constexpr unsigned int height = 1080;

	// Wide 1080
	//constexpr unsigned int width = 1920 * 2;
	//constexpr unsigned int height = 1080;

	// Wide 1440
	//constexpr unsigned int width = 2560 * 2;
	//constexpr unsigned int height = 1440;
}

namespace Nova {

	struct RenderState {
		std::pair<unsigned int, unsigned int> frame_size;
		Shader* shader;
		Buffer::Context* buffer_context;
		Buffer::Frame* framebuffer;

		RenderState(Buffer::Frame* fbuff) : buffer_context(Buffer::Context::Create()) , framebuffer(fbuff) {
			constexpr float vb_data[] = {
				-1.0f,  1.0f,	0.0f, 1.0f,
				 1.0f,  1.0f,	1.0f, 1.0f,
				-1.0f, -1.0f,	0.0f, 0.0f,
				 1.0f, -1.0f,	1.0f, 0.0f,
			};
			constexpr size_t ib_size = 6;
			unsigned int ib_data[ib_size] = {
				0, 1, 2, 2, 1, 3
			};

			auto vb = Buffer::Vertex::Create(sizeof(vb_data), vb_data);
			auto ib = Buffer::Index::Create(ib_size, ib_data);

			buffer_context->bind();
			buffer_context->buffer(ib);
			buffer_context->buffer(vb, {
				{ Nova::Buffer::Type::Float2, "v_pos" },
				{ Nova::Buffer::Type::Float2, "v_tex" },
				});

			shader = Nova::Shader::Create("Nova/res/shader/main_render.glsl");
			auto output = Nova::Texture2D::Create(FrameOutput::width, FrameOutput::height, {
				{ Nova::Texture::Colour::Type::RGB }
			});
			shader->Upload()->Int("u_tex", 0);
			framebuffer->attach_colour(output);

			framebuffer->validate();

			buffer_context->unbind();
			shader->unbind();
			framebuffer->unbind();
		}

		~RenderState() {
			delete buffer_context;
			delete shader;
			delete framebuffer;
		}
	};

	static RenderState* render_state = nullptr;

	bool Render::Initialise() {
		render_state = new RenderState(
			Buffer::Frame::Create()
		);
		auto& window_prop = App().window().properties();
		render_state->frame_size.first = window_prop.width;
		render_state->frame_size.second = window_prop.height;
		return Render::Command::Initialise();
	}

	bool Render::Termintate() {
		return Render::Command::Termintate();
		delete render_state;
	}

	void Render::FrameSize(unsigned int width, unsigned int height) {
		render_state->frame_size.first = width;
		render_state->frame_size.second = height;
	}

	void Render::Scene(bool b) {
		render_state->framebuffer->bind();
		Render::Command::Viewport(FrameOutput::width, FrameOutput::height);
		Render::Command::Clear();
	}

	void Render::Scene() {
		render_state->framebuffer->unbind();
		Render::Command::Viewport(render_state->frame_size.first, render_state->frame_size.second);
		render_state->framebuffer->get_colour()->bind();
		render_state->shader->bind();
		render_state->buffer_context->bind();
		Command::Draw(render_state->buffer_context);
	}

}