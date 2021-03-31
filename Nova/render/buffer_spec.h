#pragma once
#include "npch.h"
#include "buffer.h"
#include "buffer_type.h"

namespace Nova::Buffer {

	class NOVA_API VertexSpec {
	public:
		struct Element {
			Type type;
			unsigned int offset;
			unsigned int size, count;
			bool normalise;

			#ifdef _DEBUG
			std::string name;
			Element(Type type, const std::string& name, bool normalise=false)
				: type(type), offset(0), size(TypeSize(type)), count(TypeCount(type)), normalise(normalise), name(name) {}
			#else
			Element(Type type, const std::string& name, bool normalise=false)
				: type(type), offset(0), size(TypeSize(type)), count(TypeCount(type)), normalise(normalise) {}
			#endif // _DEBUG

		};

		VertexSpec() = default;
		VertexSpec(const std::initializer_list<Element>& types) : m_elements(types) {
			calculate();
		}

		const unsigned int& stride() const { return m_stride; }

		inline std::vector<Element>::iterator begin() { return m_elements.begin(); }
		inline std::vector<Element>::iterator end() { return m_elements.end(); }
		inline const std::vector<Element>::const_iterator begin() const { return m_elements.cbegin(); }
		inline const std::vector<Element>::const_iterator end() const { return m_elements.cend(); }

	private:
		std::vector<Element> m_elements;
		unsigned int m_stride = 0;

		const unsigned int& calculate() {
			m_stride = 0;
			for (auto& elm : m_elements) {
				elm.offset = m_stride;
				m_stride += elm.size;
			}
			return m_stride;
		}
	};

}