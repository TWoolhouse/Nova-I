#include "npch.h"
#include "application.h"

namespace Nova {

	Application* Application::s_instance = nullptr;

	Application::Application() {
		s_instance = this;
		m_active = true;
	}
	Application ::~Application() {
		s_instance = nullptr;
	}

}