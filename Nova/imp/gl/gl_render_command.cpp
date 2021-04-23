#include "npch.h"

#ifdef NOVA_OPENGL
#include "gl_bind_helper.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "render/command.h"
#include "gl_window.h"

#include "core/application.h"

#ifndef NDEBUG
#include "buffer/gl_buffer_array.h"
#endif // NDEBUG

static GLFWwindow* s_window;

namespace Nova {

	bool Render::Command::Initialise() {
		auto& window = App().window();
		s_window = static_cast<GLFWwindow*>(window.window());
		Viewport(window.properties().width, window.properties().height);

		// Needs flags to Set?
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Black Screen!
		// glEnable(GL_DEPTH_TEST);

		return true;
	}

	bool Render::Command::Termintate() {
		s_window = nullptr;
		return true;
	}

	void Render::Command::SwapBuffers() {
		glfwSwapBuffers(s_window);
	}

	void Render::Command::Viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
		glViewport(x, y, width, height);
	}

	void Render::Command::Viewport(unsigned int width, unsigned int height) {
		glViewport(0, 0, width, height);
	}

	void Render::Command::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Render::Command::ClearColour(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void Render::Command::Draw(Buffer::Context* bc) {
		nova_gl_bind(GL_VERTEX_ARRAY_BINDING, static_cast<OpenGL::BufferVertexArray*>(bc)->m_id);
		glDrawElements(GL_TRIANGLES, bc->index().count(), GL_UNSIGNED_INT, nullptr);
	}

	void Render::Command::VSync(const bool flag) {
		glfwSwapInterval(flag);
	}

}

#endif // NOVA_OPENGL
