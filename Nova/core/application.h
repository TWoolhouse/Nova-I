#pragma once
#include "npch.h"

namespace Nova {

	class NOVA_API Application {
	public:
		Application();
		virtual ~Application();

		const bool active() const { return m_active; }

	private:
		static Application* s_instance;
		friend inline static Application& App();

		bool m_active = false;
	};

	inline static Application& App() { return *Application::s_instance; }

	Application* Create();

}