#pragma once
#include "npch.h"
#include "draw.h"
#include "../render_batch.h"
#include "../shader.h"

namespace Nova::RenderDraw {

	class NOVA_API Quad : public Draw {
	public:
		constexpr static unsigned int BATCH_SIZE = 1024;
		struct Block : RenderBatch::Block {
			static Nova::Buffer::Vertex::Spec Layout;
			mlb::mat4 mat{ 1.0f };
			mlb::vec4 colour{ 1.0f };
			float texture;
			mlb::vec2 tex_pos[4];
		};

		static void Initialise();
		static void Terminate();
		static void Flush();
		static RenderBatch::Buffer<Quad::Block, BATCH_SIZE>* batch;
		static Star<Shader> shader;
		static TextureMap<Quad> textures;
	};

}