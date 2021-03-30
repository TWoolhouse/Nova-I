#pragma once
#include "npch.h"
#include "window.h"
#include "event/event.h"

namespace Nova {

	class NOVA_API Application {
	public:
		static Application* Create();
		Application();
		virtual ~Application();

		const bool active() const { return m_active; }

		void main();

	private:
		void event_callback(Event::Event& event);
		static Application* s_instance;
		friend inline static Application& App();

		bool m_active = false;
		Window* m_window;
	};

	inline static Application& App() { return *Application::s_instance; }

}