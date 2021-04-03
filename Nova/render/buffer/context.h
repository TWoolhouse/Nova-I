#pragma once
#include "npch.h"
#include "buffer.h"

namespace Nova::Buffer {

	class NOVA_API Context {
	public:
		static Context* Create();
		Context() : m_index_buffer(nullptr) {}
		virtual ~Context() {}

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void buffer(Vertex* buffer, const Vertex::Spec& spec) = 0;
		virtual void buffer(Index* buffer) = 0;

		const Index& index() const { return *m_index_buffer; }
		const std::vector<Vertex*>& vertex() const { return m_vertex_buffers; }

	protected:
		Index* m_index_buffer;
		std::vector<Vertex*> m_vertex_buffers;
	};

}