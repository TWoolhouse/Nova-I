#include "npch.h"
#include "application.h"
#include "deltatime.h"
#include "event/window.h"
#include "render/command.h"

namespace Nova {

	Application* Application::s_instance = nullptr;

	Application::Application() {
		s_instance = this;
		DeltaTime::update();
		m_window = Window::Create(
			std::bind(&Application::event_callback, this, std::placeholders::_1)
		);
		Render::Initialise();
		DeltaTime::update();
		m_active = true;
	}
	Application ::~Application() {
		Render::Termintate();
		delete m_window;
		if (s_instance == this)
			s_instance = nullptr;
	}

	void Application::main() {
		m_window->update();
		DeltaTime::update();
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