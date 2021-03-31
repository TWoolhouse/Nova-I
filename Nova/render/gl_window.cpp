#include "npch.h"
#ifdef NOVA_OPENGL
#include <GL/glew.h>
#include "gl_window.h"

#include "event/window.h"
#include "event/mouse.h"
#include "event/key.h"

namespace Nova {

	Window* Window::Create(const Window::Properties& properties) {
		return new OpenGL::Window(properties);
	}

	namespace OpenGL {

		static unsigned int s_instances = 0;

		Window::Window(const Nova::Window::Properties& properties)
			: Nova::Window(properties), m_window(nullptr) {
			if (!s_instances && !glfwInit())
				return;

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			// glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			m_window = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.name.c_str(), nullptr, nullptr);
			
			glfwMakeContextCurrent(m_window);
			// m_context = new Renderer::ImplContext(m_window);

			glfwSetWindowUserPointer(m_window, &m_properties);
			if (!s_instances++ && glewInit() != GLEW_OK) {
				delete this;
				return;
			}

			// glfwSwapInterval(0); // vsnyc

			// Renderer::Command::ClearColour();

			// Set Event Callbacks //

			// Window Events
			glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
				Properties& cb = *static_cast<Properties*>(glfwGetWindowUserPointer(window));
				Event::WindowClose event;
				cb.event_cb(event);
			});

			glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int gain) {
				Properties& cb = *static_cast<Properties*>(glfwGetWindowUserPointer(window));
				if (gain) {
					Event::WindowFocusGain event;
					cb.event_cb(event);
				} else {
					Event::WindowFocusLost event;
					cb.event_cb(event);
				}
			});

			glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int x_pos, int y_pos) {
				Properties& cb = *static_cast<Properties*>(glfwGetWindowUserPointer(window));
				Event::WindowMove event(x_pos, y_pos);
				cb.event_cb(event);
			});

			glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
				Properties& cb = *static_cast<Properties*>(glfwGetWindowUserPointer(window));
				Event::WindowResize event(width, height);
				cb.event_cb(event);
			});

			// Mouse Events
			glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x_pos, double y_pos) {
				Properties& cb = *static_cast<Properties*>(glfwGetWindowUserPointer(window));
				Event::MouseMove event = Event::MouseMove(static_cast<unsigned int>(x_pos), static_cast<unsigned int>(y_pos));
				cb.event_cb(event);
			});

			glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
				Properties& cb = *static_cast<Properties*>(glfwGetWindowUserPointer(window));
				switch (action) {
				case (GLFW_PRESS): {
					Event::MouseButtonPress event(Input::WindowMouseCode(button));
					cb.event_cb(event);
					break;
				}
				case (GLFW_RELEASE): {
					Event::MouseButtonRelease event(Input::WindowMouseCode(button));
					cb.event_cb(event);
					break;
				}
				default:
					break;
				}
			});

			glfwSetScrollCallback(m_window, [](GLFWwindow* window, double x_off, double y_off) {
				Properties& cb = *static_cast<Properties*>(glfwGetWindowUserPointer(window));
				Event::MouseScroll event(static_cast<unsigned int>(x_off), static_cast<unsigned int>(y_off));
				cb.event_cb(event);
			});

			// Key Events
			glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				Properties& cb = *static_cast<Properties*>(glfwGetWindowUserPointer(window));

				switch (action) {
				case (GLFW_PRESS): {
					Event::KeyPress event(Input::WindowKeyCode(key), 0);
					cb.event_cb(event);
					break;
				}
				case (GLFW_RELEASE): {
					Event::KeyRelease event(Input::WindowKeyCode(key));
					cb.event_cb(event);
					break;
				}
				case (GLFW_REPEAT): {
					Event::KeyPress event(Input::WindowKeyCode(key), 1);
					cb.event_cb(event);
					break;
				}
				default:
					break;
				}
			});

		}

		Window::~Window() {
			glfwDestroyWindow(m_window);
			if (!--s_instances)
				glfwTerminate();
		}

		void Window::update() {

			glfwSwapBuffers(m_window);
			//m_context->swap_buffers();

			glfwPollEvents();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//m_context->clear_colour(0.0f, 0.0f, 0.0f, 1.0f);
			//Renderer::Command::Clear();
		}

	}
}

#endif // NOVA_OPENGL

