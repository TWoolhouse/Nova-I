#include "npch.h"
#include "application.h"
#include "event/window.h"
#include "render/command.h"

namespace Nova {

	Application* Application::s_instance = nullptr;

	Application::Application() {
		s_instance = this;
		m_window = Window::Create();
		m_window->properties().event_cb = std::bind(&Application::event_callback, this, std::placeholders::_1);
		Render::Initialise();
		m_active = true;
	}
	Application ::~Application() {
		Render::Termintate();
		delete m_window;
		s_instance = nullptr;
	}

	void Application::main() {
		m_window->update();
		Render::Scene(true);
		update();
		Render::Scene();
	}

	void Application::event_callback(Event::Event& event) {
		if (event.is<Event::WindowClose>()) {
			m_active = false;
			return;
		}
		this->event(event);
	}

}