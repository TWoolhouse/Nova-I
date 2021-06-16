#include "npch.h"

#ifdef NOVA_OPENGL
#include "gl_helper.h"
#include <GL/glew.h>
#include <stdexcept>
#include <iostream>

#ifndef NOVA_RELEASE

void _nova_gl_check_bind(unsigned int target, int name) {
	int ret;
	glGetIntegerv(target, &ret);
	nova_assert(name == ret, "Object not Bound During Bound Operation");
}

void _nova_gl_error() {
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "GL Error: " << err << std::endl;
	}
}

#endif // !NOVA_RELEASE

#endif // NOVA_OPENGL
