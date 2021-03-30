#pragma once
#include "npch.h"
#include "core/window.h"
#include <GLFW/glfw3.h>

namespace Nova::OpenGL {
	class Window : public Nova::Window {
	public:
		Window(const Nova::Window::Properties& properties);
		virtual ~Window() override;
		virtual void update() override;
		virtual void* window() const override { return m_window; }
	private:
		GLFWwindow* m_window;
	};
}
