#pragma once
#include "npch.h"
#include "type.h"

namespace Nova::Buffer {

	class NOVA_API Vertex {
	public:
		class NOVA_API Spec {
		public:
			struct Element {
				Type type;
				unsigned int offset;
				unsigned int size, count;
				bool normalise;

				#ifndef NDEBUG
				std::string name;
				Element(Type type, const std::string& name, bool normalise = false)
					: type(type), offset(0), size(TypeSize(type)), count(TypeCount(type)), normalise(normalise), name(name) {}
				#else
				Element(Type type, const std::string& name, bool normalise = false)
					: type(type), offset(0), size(TypeSize(type)), count(TypeCount(type)), normalise(normalise) {}
				#endif // NDEBUG
			};

			Spec(const std::initializer_list<Element>& types) : m_elements(types) {
				calculate();
			}

			const unsigned int& stride() const { return m_stride; }
			inline const std::vector<Element>& vector() const { return m_elements; }

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

		static Vertex* Create(const unsigned int size);
		static Vertex* Create(const unsigned int size, const void* data);

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void set(const unsigned int size, const void* data) = 0;
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