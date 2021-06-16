#include "npch.h"
#ifdef NOVA_OPENGL
#include "gl_init.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gl_window.h"

#include "event/window.h"
#include "event/mouse.h"
#include "event/key.h"

#include "render/command.h"

#include "fileio/texture.h"

namespace Nova {

	Window* Window::Create(
		std::function<void(Event::Event&)> events,
		const unsigned int& width, const unsigned int& height,
		const std::string& name, const std::string& icon) {
		return new OpenGL::Window(events, width, height, name, icon);
	}

	namespace OpenGL {

		static unsigned int s_instances = 0;

		Window::Window(
			std::function<void(Event::Event&)> events,
			const unsigned int& width, const unsigned int& height,
			const std::string& name, const std::string& icon
		) : Nova::Window(events, width, height, name, icon), m_window(nullptr) {
			OpenGL::Initialize();

			// glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);
			
			glfwMakeContextCurrent(m_window);

			glfwSetWindowUserPointer(m_window, this);
			if (!s_instances++ && glewInit() != GLEW_OK) {
				delete this;
				return;
			}

			Nova::Render::Command::Viewport(m_width, m_height);

			// Set Event Callbacks //

			// Window Events
			glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
				Window& win = *static_cast<Window*>(glfwGetWindowUserPointer(window));
				Event::WindowClose event;
				win.properties().event_callback(event);
			});

			glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int gain) {
				Window& win = *static_cast<Window*>(glfwGetWindowUserPointer(window));
				if (gain) {
					Event::WindowFocusGain event;
					win.properties().event_callback(event);
				} else {
					Event::WindowFocusLost event;
					win.properties().event_callback(event);
				}
			});

			glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int x_pos, int y_pos) {
				Window& win = *static_cast<Window*>(glfwGetWindowUserPointer(window));
				Event::WindowMove event(x_pos, y_pos);
				win.properties().event_callback(event);
			});

			glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
				Render::FrameSize(width, height);
			});

			glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
				Window& win = *static_cast<Window*>(glfwGetWindowUserPointer(window));
				win.width(width); win.height(height);
				Event::WindowResize event(width, height);
				win.properties().event_callback(event);
			});

			// Mouse Events
			glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x_pos, double y_pos) {
				Window& win = *static_cast<Window*>(glfwGetWindowUserPointer(window));
				Event::MouseMove event = Event::MouseMove(static_cast<unsigned int>(x_pos), static_cast<unsigned int>(y_pos));
				win.properties().event_callback(event);
			});

			glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
				Window& win = *static_cast<Window*>(glfwGetWindowUserPointer(window));
				switch (action) {
				case (GLFW_PRESS): {
					Event::MouseButtonPress event(Input::WindowMouseCode(button));
					win.properties().event_callback(event);
					break;
				}
				case (GLFW_RELEASE): {
					Event::MouseButtonRelease event(Input::WindowMouseCode(button));
					win.properties().event_callback(event);
					break;
				}
				default:
					break;
				}
			});

			glfwSetScrollCallback(m_window, [](GLFWwindow* window, double x_off, double y_off) {
				Window& win = *static_cast<Window*>(glfwGetWindowUserPointer(window));
				Event::MouseScroll event(static_cast<float>(x_off), static_cast<float>(y_off));
				win.properties().event_callback(event);
			});

			// Key Events
			glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				Window& win = *static_cast<Window*>(glfwGetWindowUserPointer(window));

				switch (action) {
				case (GLFW_PRESS): {
					Event::KeyPress event(Input::WindowKeyCode(key), 0);
					win.properties().event_callback(event);
					break;
				}
				case (GLFW_RELEASE): {
					Event::KeyRelease event(Input::WindowKeyCode(key));
					win.properties().event_callback(event);
					break;
				}
				case (GLFW_REPEAT): {
					Event::KeyPress event(Input::WindowKeyCode(key), 1);
					win.properties().event_callback(event);
					break;
				}
				default:
					break;
				}
			});

			OpenGL::Setup();

			const auto [w, h, i] = FileIO::Texture(m_icon, false);
			const GLFWimage ico{w, h, i};
			glfwSetWindowIcon(m_window, 1, &ico);
			FileIO::Texture(i);

		}

		Window::~Window() {
			glfwDestroyWindow(m_window);
			if (!--s_instances)
				OpenGL::Terminate();
		}

		void Window::update() {
			Render::Command::SwapBuffers();
			glfwPollEvents();
			Render::Command::Clear();
		}

	}
}

#endif // NOVA_OPENGL
