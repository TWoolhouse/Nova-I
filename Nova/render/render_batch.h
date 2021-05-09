#pragma once
#include "npch.h"
#include "render.h"
#include "buffer/context.h"

namespace Nova::RenderBatch {

	struct Block {
	public:
		static Nova::Buffer::Vertex::Spec Layout;
	};

	template<typename T, unsigned int S>
	class NOVA_API Buffer {
	public:
		Buffer() : m_buffer(new T[S]), m_ptr(m_buffer),
			m_context(Nova::Buffer::Context::Create()),
			m_vertex(Nova::Buffer::Vertex::Create(S * sizeof(T))), m_index(nullptr) {
			static_assert(std::is_base_of_v<Block, T> && "Buffer Type must derive from Block");
			m_context->buffer(m_vertex, T::Layout);
			unsigned int* ibuffer = new uint32_t[S];
			for (size_t i = 0; i < S; i++) { ibuffer[i] = i; }
			m_index = Nova::Buffer::Index::Create(ibuffer, S);
			m_context->buffer(m_index);
		}

		~Buffer() {
			delete m_vertex;
			delete m_index;
			delete m_context;
			delete[] m_buffer;
		}

		Nova::Buffer::Context& context() { return *m_context; }
		Nova::Buffer::Vertex& vertex() { return *m_vertex; }
		constexpr static unsigned int size = S;
		T& next() { return *m_ptr++; }
		T* data() { return m_buffer; }
		const unsigned int count() const { return m_ptr - m_buffer; }
		void reset() { m_ptr = m_buffer; }
	protected:
		T* m_buffer, * m_ptr;
		Nova::Buffer::Context* m_context;
		Nova::Buffer::Vertex* m_vertex;
		Nova::Buffer::Index* m_index;
	};

}