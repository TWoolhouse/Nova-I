#pragma once
#include "npch.h"
#include "buffer.h"
#include "buffer_spec.h"

namespace Nova::Buffer {

	class NOVA_API Context {
	public:
		static Context* Create();

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void buffer(Vertex* buffer, const VertexSpec& spec) = 0;
		virtual void buffer(Index* buffer) = 0;
	};

}