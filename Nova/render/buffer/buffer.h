#pragma once
#include "npch.h"

namespace Nova::Buffer {

	class NOVA_API Vertex {
	public:
		static Vertex* Create(const unsigned int size);
		static Vertex* Create(const unsigned int size, const float* data);

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void set(const unsigned int size, const float* data) = 0;
		virtual ~Vertex() {};
	};

	class NOVA_API Index {
	public:
		static Index* Create(const unsigned int count);
		static Index* Create(const unsigned int count, const unsigned int* indices);
		Index(const unsigned int count) : m_count(count) {}

		virtual void bind() = 0;
		virtual void unbind() = 0;
		const unsigned int count() const { return m_count; }

		virtual ~Index() {};
	protected:
		unsigned int m_count;
	};

}