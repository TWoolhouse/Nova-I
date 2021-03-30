#pragma once
#include "npch.h"

namespace Nova {

	class NOVA_API Window {
	public:
		struct Properties {
			unsigned int width, height;
			std::string name;
			Properties(
				const unsigned int width = 1280,
				const unsigned int height = 720,
				const std::string name = "Nova Engine"
			) : width(width), height(height), name(name) {}
		};

		static Window* Create(const Properties& properties = Properties());
		Window(const Properties& properties) : m_properties(properties) {}
		virtual ~Window() {}
		virtual void update() = 0;

		virtual void* window() const = 0;
		Properties& properties() { return m_properties; }

	protected:
		Properties m_properties;
	};

}