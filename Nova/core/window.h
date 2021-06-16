#pragma once
#include "npch.h"
#include "event/event.h"

namespace Nova {

	class NOVA_API Window {
	protected:
		struct Properties;
	public:
		static Window* Create(
			std::function<void(Event::Event&)> events,
			const unsigned int& width = 1280,
			const unsigned int& height = 720,
			const std::string& name = "Nova Engine",
			const std::string& icon = "Nova/texture/nova.png"
		);
		Window(
			std::function<void(Event::Event&)> events,
			const unsigned int& width, const unsigned int& height,
			const std::string& name, const std::string& icon
		) : m_properties({events}), m_width(width), m_height(height), m_name(name), m_icon(icon) {}
		virtual ~Window() {}
		virtual void update() = 0;

		virtual void* window() const = 0;

		const unsigned int& width() const { return m_width; }
		const unsigned int& height() const { return m_height; }
		const std::string& name() const { return m_name; }
		const std::string& icon() const { return m_icon; }

		Properties& properties() { return m_properties; }

		const unsigned int& width(const unsigned int& width) { resize(width, m_height) ; return m_width; }
		const unsigned int& height(const unsigned int& height) { resize(m_width, height); return m_height; }
		virtual void resize(const unsigned int& width, const unsigned int& height) = 0;
		virtual const std::string& name(const std::string& name) = 0;
		virtual const std::string& icon(const std::string& icon) = 0;

	protected:
		struct Properties {
			std::function<void(Event::Event&)> event_callback;
		};
		Properties m_properties;
		unsigned int m_width, m_height;
		std::string m_name, m_icon;
	};

}