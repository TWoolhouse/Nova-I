#include "npch.h"
#ifdef NOVA_OPENGL
#include <GL/glew.h>
#include "gl_window.h"

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

			// Set Event Callbacks

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

