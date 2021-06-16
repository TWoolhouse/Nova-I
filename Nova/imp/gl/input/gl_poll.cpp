#include "npch.h"

#ifdef NOVA_OPENGL
#include <GLFW/glfw3.h>
#include "core/application.h"
#include "input/poll.h"

namespace Nova::Input {

	const bool PollWin(const Key& key) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Nova::App().window().window());
		int state = glfwGetKey(window, WindowCode(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	const std::pair<int, int> Poll() {
		GLFWwindow* window = static_cast<GLFWwindow*>(Nova::App().window().window());
		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, &y_pos);
		return {x_pos, y_pos};
	}

	const bool PollWin(const Mouse& button) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Nova::App().window().window());
		int state = glfwGetMouseButton(window, WindowCode(button));
		return state == GLFW_PRESS;
	}

}

#endif // NOVA_OPENGL
