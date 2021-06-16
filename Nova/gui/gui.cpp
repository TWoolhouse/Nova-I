#include "npch.h"
#include "gui.h"
#include "event/key.h"
#include "event/mouse.h"
#include "event/window.h"

#include <imgui/imgui.h>

namespace Nova::gui {

	App::App() {
		#ifndef NOVA_RELEASE
		IMGUI_CHECKVERSION();
		#endif !NOVA_RELEASE
	}

	void App::event(Nova::Event::Event& event) {
		if (m_block) {
			auto& io = ImGui::GetIO();
			event.done |= event.cat<Nova::Event::Key>() & io.WantCaptureKeyboard;
			event.done |= event.cat<Nova::Event::Mouse>() & io.WantCaptureMouse;
		}
	}

	void App::setup() {
		auto& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		io.IniFilename = "Nova/gui.ini";

		auto font = io.Fonts->AddFontFromFileTTF("Nova/font/CascadiaCode_VTT.ttf", 17.0f);
		io.FontDefault = font;
	}

}
