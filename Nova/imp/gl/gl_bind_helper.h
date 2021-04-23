#pragma once

#ifndef NDEBUG

#define nova_gl_bind(target, name) _nova_gl_check_bind(target, name)
void _nova_gl_check_bind(unsigned int target, int name);

#else

#define nova_gl_bind(target, name) ;

#endif // !NDEBUG
