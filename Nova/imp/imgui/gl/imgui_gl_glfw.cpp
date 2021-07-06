#include "npch.h"
#include "../imgui_export.h"

#ifdef NOVA_OPENGL
#pragma warning(disable : 4996)
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.cpp>
#endif // NOVA_OPENGL
