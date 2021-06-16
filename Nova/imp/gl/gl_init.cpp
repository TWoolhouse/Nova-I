#include "npch.h"

#ifdef NOVA_OPENGL
#include "gl_init.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "render/command.h"

namespace Nova::OpenGL {

	static bool s_instance = false;

	void GLAPIENTRY callback_error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		std::cerr << "GL: " << (GL_DEBUG_TYPE_ERROR ? "ERROR " : "") <<
			"Type: " << type <<
			" Severity: " << severity <<
			" -> " << message <<
			std::endl;
	}

	bool Initialize() {
		if (!s_instance && !glfwInit()) {
			#ifndef NOVA_RELEASE
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback(callback_error, 0);
			#else
			glDisable(GL_DEBUG_OUTPUT);
			#endif // !NOVA_RELEASE

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			
			return false;
		}
		s_instance = true;
		return true;
	}

	void Setup() {
		Nova::Render::Command::VSync(true);
		Nova::Render::Command::Depth(true);
	}

	bool Terminate() {
		if (s_instance) {
			glfwTerminate();
			s_instance = false;
		}
		return false;
	}

}

#endif // NOVA_OPENGL