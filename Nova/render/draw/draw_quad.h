#pragma once
#include "npch.h"
#include "draw.h"
#include "render/render_batch.h"

namespace Nova::RenderDraw {

	class NOVA_API Quad : public Draw {
	public:
		constexpr static unsigned int BATCH_SIZE = 1000;
		struct Block : RenderBatch::Block {
			static Nova::Buffer::Vertex::Spec Layout;
			mlb::vec2 pos;
			mlb::vec2 size{ 1.0f };
		};

		static void Initialise();
		static void Terminate();
		static void Flush();
		static RenderBatch::Buffer<Quad::Block, BATCH_SIZE>* batch;
		static Shader* shader;
	};

}