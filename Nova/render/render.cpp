#include "npch.h"
#include "render.h"
#include "command.h"
#include "buffer/context.h"
#include "buffer/frame.h"
#include "shader.h"
#include "camera.h"
#include "core/application.h"

#include "draw/draw_quad.h"

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
		mlb::mat4 matrix;

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

			shader = Nova::Shader::Create("Nova/shader/main_render.glsl");
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

	static RenderState* rs = nullptr;

	bool Render::Initialise() {
		rs = new RenderState(
			Buffer::Frame::Create()
		);
		auto& window_prop = App().window().properties();
		rs->frame_size.first = window_prop.width;
		rs->frame_size.second = window_prop.height;

		// Sub Renderers
		RenderDraw::Quad::Initialise();

		return Render::Command::Initialise();
	}

	bool Render::Termintate() {
		RenderDraw::Quad::Terminate();

		// Sub Renderers
		Render::Command::Termintate();

		delete rs;
		return true;
	}

	void Render::FrameSize(unsigned int width, unsigned int height) {
		rs->frame_size.first = width;
		rs->frame_size.second = height;
	}

	void Render::Draw(Camera* camera) {
		memcpy(&rs->matrix, &camera->compute(), sizeof(mlb::mat4));
		rs->framebuffer->bind();
		Render::Command::Viewport(FrameOutput::width, FrameOutput::height);
		Render::Command::Clear();
	}

	void Render::Draw() {
		Flush();
		rs->framebuffer->unbind();
		Render::Command::Viewport(rs->frame_size.first, rs->frame_size.second);
		rs->framebuffer->get_colour()->bind();
		rs->shader->bind();
		rs->buffer_context->bind();
		Command::Draw(rs->buffer_context);
	}

	void Render::Flush() {
		RenderDraw::Quad::Flush();
	}

}