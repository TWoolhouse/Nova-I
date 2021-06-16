#include "npch.h"
#include "render.h"
#include "command.h"
#include "render_state.h"

#include "camera.h"
#include "core/application.h"

#include "draw.h"
#include "draw/draw_quad.h"

namespace FrameOutput {
	// 4K
	//constexpr unsigned int width = 3840;
	//constexpr unsigned int height = 2160;

	// 720
	//constexpr unsigned int width = 1280;
	//constexpr unsigned int height = 720;

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

	RenderState::RenderState(Buffer::Frame* fbuff)
		: buffer_context(Buffer::Context::Create()), framebuffer(fbuff), blank_texture(Texture2D::Create(1, 1, {})) {
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

		auto vb = Buffer::Vertex::Create(vb_data, sizeof(vb_data));
		auto ib = Buffer::Index::Create(ib_data, ib_size);

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

		{ // Blank Texture Data
			unsigned int data = 0xffffffff;
			blank_texture->set((unsigned char*)(&data), 1);
		}

		{ // Generate Uniform Buffers
			auto gen_buffers = Nova::Shader::Create("Nova/shader/buffers.glsl");

			uniform = Buffer::Uniform::Create(gen_buffers, "camera", {
				"matrix",
			});

		}

		uniform->set("matrix", &matrix);

		buffer_context->unbind();
		shader->unbind();
		framebuffer->unbind();
	}

	RenderState::~RenderState() {
		delete buffer_context;
		delete framebuffer;
	}

	static RenderState* rs = nullptr;
	RenderState& Nova::RenderState::Get() {
		return *rs;
	}

	bool Render::Initialise() {
		rs = new RenderState(
			Buffer::Frame::Create()
		);
		rs->frame_size.first = App().window().width();
		rs->frame_size.second = App().window().height();

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
		rs->uniform->set("matrix", &rs->matrix);
		rs->framebuffer->bind();
		auto& size = rs->framebuffer->get_colour()->size();
		Render::Command::Viewport(size.x, size.y);
		Render::Command::Clear();
	}

	void Render::Draw() {
		rs->uniform->bind(0);
		Flush();
		rs->framebuffer->unbind();
	}

	void Render::Frame() {
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