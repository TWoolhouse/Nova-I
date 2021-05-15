#include "npch.h"
#include "imgui_export.h"

#ifdef NOVA_OPENGL
#pragma warning(disable : 4996)
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.cpp>
#include <imgui/backends/imgui_impl_opengl3.cpp>
#endif // NOVA_OPENGL
