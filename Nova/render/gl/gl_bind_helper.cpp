#include "npch.h"

#ifdef NOVA_OPENGL
#include "gl_bind_helper.h"
#include <GL/glew.h>
#include <stdexcept>

#ifndef NDEBUG

void _nova_gl_check_bind(unsigned int target, int name) {
	int ret;
	glGetIntegerv(target, &ret);
	if (ret != name) {
		throw std::runtime_error("Object not Bound During Bound Operation");
	}
}

#endif // !NDEBUG

#endif // NOVA_OPENGL
