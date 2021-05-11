#include "npch.h"

#ifdef NOVA_OPENGL
#include "gl_init.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Nova::OpenGL {

	static bool s_instance = false;

	bool Initialize() {
		if (!s_instance && !glfwInit())
			return false;
		s_instance = true;
		return true;
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