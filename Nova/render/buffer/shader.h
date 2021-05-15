#pragma once
#include "npch.h"
#include "type.h"
#include "../shader.h"

namespace Nova::Buffer {

	class NOVA_API Shader {
	public:
		class NOVA_API Spec {
		public:
			struct Element {
				unsigned int offset, size;
				std::string name;
				Element() : offset(std::numeric_limits<unsigned int>::max()), size(0), name() {}
				Element(const std::string& name)
					: offset(std::numeric_limits<unsigned int>::max()), size(0), name(name) {}
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

		static Star<Shader> Create(const Star<Nova::Shader>& shader, const std::string& name, const Spec& spec);
		Shader(const Spec& spec) : m_layout(spec) {}

		virtual void bind(unsigned int slot=0) = 0;
		virtual void unbind() = 0;

		virtual void get(const std::string& name, void* const data) = 0;
		virtual void get(const std::string& name, void* const data, const unsigned int size, const unsigned int offset = 0) = 0;

		virtual void set(const std::string& name, const void* data) = 0;
		virtual void set(const std::string& name, const void* data, const unsigned int size, const unsigned int offset = 0) = 0;
		virtual void set(const std::string& name, const unsigned int size) = 0;

		virtual void sync() = 0;

		Spec::Element& operator[](const std::string& name) { return m_layout.elements()[name]; }
		const Spec& layout() const { return m_layout; }

		virtual ~Shader() {};
	protected:
		Spec m_layout;
	};

}
