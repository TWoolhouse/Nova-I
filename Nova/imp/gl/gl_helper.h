#pragma once

#ifndef NOVA_RELEASE

#define nova_gl_bind(target, name) _nova_gl_check_bind(target, name)
void _nova_gl_check_bind(unsigned int target, int name);

#define nova_gl_error() _nova_gl_error()
void _nova_gl_error();

#else

#define nova_gl_bind(target, name)
#define nova_gl_error()

#endif // !NOVA_RELEASE
