#pragma once
#include "npch.h"
#include "core/window.h"
#include <GLFW/glfw3.h>

namespace Nova::OpenGL {
	class Window : public Nova::Window {
	public:
		Window(
			std::function<void(Event::Event&)> events,
			const unsigned int& width, const unsigned int& height,
			const std::string& name, const std::string& icon
		);
		virtual ~Window() override;
		virtual void update() override;
		virtual void* window() const override { return m_window; }
	private:
		GLFWwindow* m_window;
	};
}
