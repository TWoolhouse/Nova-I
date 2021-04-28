#include "npch.h"
#include "draw_quad.h"

namespace Nova {

	Buffer::Vertex::Spec RenderDraw::Quad::Block::Layout = {
		{ Nova::Buffer::Type::Mat4, "mat" },
		{ Nova::Buffer::Type::Float4, "colour" },
	};
	RenderBatch::Buffer<RenderDraw::Quad::Block, RenderDraw::Quad::BATCH_SIZE>* RenderDraw::Quad::batch = nullptr;
	Shader* RenderDraw::Quad::shader = nullptr;

	void RenderDraw::Quad::Initialise() {
		batch = new RenderBatch::Buffer<Block, BATCH_SIZE>;
		shader = Shader::Create({
			ShaderSource::Create("Nova/shader/draw/vert.glsl"),
			ShaderSource::Create("Nova/shader/draw/frag.glsl"),
			ShaderSource::Create("Nova/shader/draw/quad.geom.glsl"),
		});
	}
	void RenderDraw::Quad::Terminate() {
		delete batch;
		delete shader;
	}

	void Render::Draw::Quad(const mlb::mat4& mat, const mlb::vec4& col) {
		if (RenderDraw::Quad::batch->count() >= RenderDraw::Quad::batch->size) {
			RenderDraw::Quad::Flush();
		}

		auto& quad = RenderDraw::Quad::batch->next();
		quad.mat = mat;
		quad.colour = col;
	}

}
