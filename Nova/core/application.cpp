#include "npch.h"
#include "application.h"

namespace Nova {

	Application* Application::s_instance = nullptr;

	Application::Application() {
		s_instance = this;
		m_window = Window::Create();
		m_active = true;
	}
	Application ::~Application() {
		delete m_window;
		s_instance = nullptr;
	}

	void Application::main() {
		m_window->update();
	}

}