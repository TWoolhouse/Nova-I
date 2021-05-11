#include "npch.h"

#ifdef NOVA_OPENGL
#include "gl_helper.h"
#include <GL/glew.h>
#include <stdexcept>
#include <iostream>

#ifndef NDEBUG

void _nova_gl_check_bind(unsigned int target, int name) {
	int ret;
	glGetIntegerv(target, &ret);
	assert(name == ret && "Object not Bound During Bound Operation");
}

void _nova_gl_error() {
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "GL Error: " << err << std::endl;
	}
}

#endif // !NDEBUG

#endif // NOVA_OPENGL
