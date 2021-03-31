#include "npch.h"
#include "application.h"
#include "event/window.h"

namespace Nova {

	Application* Application::s_instance = nullptr;

	Application::Application() {
		s_instance = this;
		m_window = Window::Create();
		m_window->properties().event_cb = std::bind(&Application::event_callback, this, std::placeholders::_1);
		m_active = true;
	}
	Application ::~Application() {
		delete m_window;
		s_instance = nullptr;
	}

	void Application::main() {
		m_window->update();
		update();
	}

	void Application::event_callback(Event::Event& event) {
		if (event.is<Event::WindowClose>()) {
			m_active = false;
			return;
		}
		this->event(event);
	}

}