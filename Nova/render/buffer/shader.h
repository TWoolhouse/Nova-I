#pragma once
#include "npch.h"
#include "type.h"
#include "render/shader.h"

namespace Nova::Buffer {

	class NOVA_API Shader {
	public:
		class NOVA_API Spec {
		public:
			struct Element {
				unsigned int offset, size;
				std::string name;
				Element() : offset(0), size(0), name() {}
				Element(const std::string& name)
					: offset(0), size(0), name(name) {}
			};

			Spec(const std::initializer_list<Element>& types) : m_elements(types.size()) {
				for (auto& elm : types) {
					m_elements[elm.name] = elm;
				}
			}
			Spec(const std::initializer_list<std::string>& names) : m_elements(names.size()) {
				for (auto& name : names) {
					m_elements[name] = {name};
				}
			}

			inline std::unordered_map<std::string, Element>& elements() { return m_elements; }

		protected:
			std::unordered_map<std::string, Element> m_elements;
		};

		static Shader* Create(Nova::Shader* shader, const std::string& name, const Spec& spec);
		Shader(const Spec& spec) : m_layout(spec) {}

		virtual void bind(unsigned int slot=0) = 0;
		virtual void unbind() = 0;

		virtual void get(const std::string& name, void* const data) = 0;
		virtual void get(const std::string& name, const unsigned int size, void* const data) = 0;
		virtual void set(const std::string& name, const void* data) = 0;
		virtual void set(const std::string& name, const unsigned int size, const void* data) = 0;

		inline Spec::Element& operator[](const std::string& name) { return m_layout.elements()[name]; }
		const Spec& layout() const { return m_layout; }

		virtual ~Shader() {};
	protected:
		Spec m_layout;
	};

}