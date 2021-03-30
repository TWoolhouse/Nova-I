#include "npch.h"
#include "application.h"

namespace Nova {

	Application* Application::s_instance = nullptr;

	Application::Application() {
		s_instance = this;
	}
	Application ::~Application() {
		s_instance = nullptr;
	}

}