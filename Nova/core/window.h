#pragma once
#include "npch.h"
#include "event/event.h"

namespace Nova {

	class NOVA_API Window {
	public:
		struct Properties {
			unsigned int width, height;
			std::string name, icon;
			std::function<void(Event::Event&)> event_cb;
			Properties(
				const unsigned int& width = 1280,
				const unsigned int& height = 720,
				const std::string& name = "Nova Engine",
				const std::string& icon = "Nova/texture/nova.png"
			) : width(width), height(height), name(name), icon(icon) {}
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