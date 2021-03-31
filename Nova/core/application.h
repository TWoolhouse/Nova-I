#pragma once
#include "npch.h"
#include "window.h"
#include "event/event.h"

int main(int argc, char const* argv[]);

namespace Nova {

	class NOVA_API Application {
	public:
		static Application* Create();
		Application();
		virtual ~Application();

		const bool active() const { return m_active; }

		virtual void event(Event::Event& event) {};
		virtual void update() {};

		void event_callback(Event::Event& event);

	private:
		friend int ::main(int argc, char const* argv[]);
		void main();
		static Application* s_instance;
		friend inline static Application& App();

		bool m_active = false;
		Window* m_window;
	};

	inline static Application& App() { return *Application::s_instance; }

}
