#include "npch.h"
#include "draw_quad.h"

namespace Nova {

	Buffer::Vertex::Spec RenderDraw::Quad::Block::Layout = {
		{ Nova::Buffer::Type::Float2, "pos" },
	};
	RenderBatch::Buffer<RenderDraw::Quad::Block, RenderDraw::Quad::BATCH_SIZE>* RenderDraw::Quad::batch = nullptr;
	Shader* RenderDraw::Quad::shader = nullptr;

	void RenderDraw::Quad::Initialise() {
		batch = new RenderBatch::Buffer<Block, BATCH_SIZE>;
		shader = Shader::Create({
			ShaderSource::Create("Nova/res/shader/draw/vert.glsl"),
			ShaderSource::Create("Nova/res/shader/draw/frag.glsl"),
			//ShaderSource::Create("Nova/res/shader/draw/quad.geom.glsl"),
		});
	}
	void RenderDraw::Quad::Terminate() {
		delete batch;
		delete shader;
	}

	void Render::Draw::Quad(const mlb::vec2& pos) {
		if (RenderDraw::Quad::batch->count() >= RenderDraw::Quad::batch->size) {
			RenderDraw::Quad::Flush();
		}

		auto& quad = RenderDraw::Quad::batch->next();
		quad.pos = pos;
	}

}
