#include "npch.h"

#ifdef NOVA_OPENGL
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "gl_gui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include "core/application.h"

constexpr auto NOVA_USE_VIEWPORT = true;

namespace Nova {

	Star<gui::App> gui::App::Create() {
		return std::make_shared<OpenGL::GuiApp>();
	}

	namespace OpenGL {

		GuiApp::GuiApp() {
			m_context = ImGui::CreateContext();
			ImGui::SetCurrentContext(m_context);
			setup();
			auto& io = ImGui::GetIO();

			ImGui::StyleColorsDark();

			GLFWwindow* window = static_cast<GLFWwindow*>(Nova::App().window().window());

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 450");
		}

		GuiApp::~GuiApp() {
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext(m_context);
		}

		void GuiApp::begin() {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void GuiApp::end() {
			auto& io = ImGui::GetIO();
			auto& app = Nova::App();
			io.DisplaySize = ImVec2((float)app.window().properties().width, (float)app.window().properties().height);

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if constexpr (NOVA_USE_VIEWPORT) {
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

		}

	}

}

#endif // NOVA_OPENGL