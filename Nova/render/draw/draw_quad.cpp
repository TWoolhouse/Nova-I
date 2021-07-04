#include "npch.h"
#include <numeric>
#include "draw_quad.h"
#include "../render_state.h"

constexpr unsigned int MAX_TEXTURES = 64;

namespace Nova {

	const std::array<mlb::vec2, 4> Draw::s_quad_tex_pos = { mlb::vec2(0.0f, 0.0f), mlb::vec2(1.0f, 0.0f), mlb::vec2(0.0f, 1.0f), mlb::vec2(1.0f, 1.0f) };

	Buffer::Vertex::Spec RenderDraw::Quad::Block::Layout = {
		{ Nova::Buffer::Type::Mat4, "mat" },
		{ Nova::Buffer::Type::Float4, "colour" },
		{ Nova::Buffer::Type::Float, "texture" },
		{ Nova::Buffer::Type::Float2, "tpos0" }, { Nova::Buffer::Type::Float2, "tpos1" }, { Nova::Buffer::Type::Float2, "tpos2" }, { Nova::Buffer::Type::Float2, "tpos3" },
	};
	RenderBatch::Buffer<RenderDraw::Quad::Block, RenderDraw::Quad::BATCH_SIZE>* RenderDraw::Quad::batch = nullptr;
	Star<Shader> RenderDraw::Quad::shader;
	RenderDraw::TextureMap<RenderDraw::Quad> RenderDraw::Quad::textures{ MAX_TEXTURES };

	void RenderDraw::Quad::Initialise() {
		batch = new RenderBatch::Buffer<Block, BATCH_SIZE>;
		shader = Shader::Create({
			ShaderSource::Create("Nova/shader/draw/quad.vert.glsl"),
			ShaderSource::Create("Nova/shader/draw/quad.geom.glsl"),
			ShaderSource::Create("Nova/shader/draw/quad.frag.glsl"),
		});
		textures.clear();
		{ // Set texture array indices;
			std::array<int, MAX_TEXTURES> bindings;
			std::iota(bindings.begin(), bindings.end(), 0);
			shader->Upload()->Int("textures", 64, bindings.data());
		}
	}
	void RenderDraw::Quad::Terminate() {
		delete batch;
	}

	void Draw::Quad(const mlb::mat4& mat, const mlb::vec4& col, const Star<Texture2D>& texture, const std::array<mlb::vec2, 4>& tex_pos) {
		if (RenderDraw::Quad::batch->count() >= RenderDraw::Quad::batch->size) {
			RenderDraw::Quad::Flush();
		}
		const auto& rs = Render::State();

		const auto tex = RenderDraw::Quad::textures.index(texture);
		auto& quad = RenderDraw::Quad::batch->next();
		quad.mat = rs.matrix * mat;
		quad.colour = col;
		quad.texture = static_cast<float>(tex);
		memcpy(quad.tex_pos, tex_pos.data(), tex_pos.size() * sizeof(mlb::vec2));
	}

}
