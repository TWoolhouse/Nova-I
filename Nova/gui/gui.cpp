#include "npch.h"
#include "gui.h"
#include "ext.h"
#include "event/key.h"
#include "event/mouse.h"
#include "event/window.h"
#include "render/render.h"
#include "render/render_state.h"

namespace Nova::imgui {

	App::App() {
		#ifndef NOVA_RELEASE
		IMGUI_CHECKVERSION();
		#endif // !NOVA_RELEASE
	}

	void App::event(Nova::Event::Event& event) {
		if (m_block) {
			auto& io = ImGui::GetIO();
			event.done |= event.cat<Nova::Event::Key>() & io.WantCaptureKeyboard;
			event.done |= event.cat<Nova::Event::Mouse>() & io.WantCaptureMouse;
		}
	}

	bool& App::render_viewport(bool& open) {
		if (open) {
			Nova::imgui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 100, 100 });
			if (Nova::imgui::Begin("Viewport", &open)) {
				const auto& focus_window = Nova::imgui::IsWindowFocused();
				const auto& focus_hover = Nova::imgui::IsWindowHovered();
				block_events(!focus_window || !focus_hover);

				auto size = Nova::imgui::GetContentRegionAvail();
				auto& fb = Nova::Render::State().framebuffer;
				auto& fbsize = fb->size();
				auto& tex = fb->get_colour();
				Nova::imgui::Image(tex, size);
				if (size.x != fbsize.x || size.y != fbsize.y) {
					fb->resize(size.x, size.y);
				}
			} Nova::imgui::End();
			Nova::imgui::PopStyleVar();
		} // Viewport
		return open;
	}

	void App::setup() {
		auto& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		io.MouseDoubleClickTime = 0.5f;

		io.IniFilename = "imgui.ini";

		auto font = io.Fonts->AddFontFromFileTTF("Nova/font/CascadiaCode_VTT.ttf", 17.0f); // 24px for large
		io.FontDefault = font;

		auto& style = ImGui::GetStyle();

		// Padding
		style.WindowPadding = { 4.0, 2.0 };
		style.FramePadding = { 4.0, 2.0 };
		style.CellPadding = { 4.0, 2.0 };
		style.ItemSpacing = { 4.0, 4.0 };
		style.ItemInnerSpacing = { 4.0, 4.0 };
		style.TouchExtraPadding = { 0.0, 0.0 };

		style.IndentSpacing = 16;
		style.ScrollbarSize = 16;
		style.GrabMinSize = 12;

		// Boarders
		style.WindowBorderSize = 1;
		style.ChildBorderSize = 0;
		style.PopupBorderSize = 0;
		style.FrameBorderSize = 0;
		style.TabBorderSize = 0;

		// Rounding
		style.WindowRounding = 8;
		style.ChildRounding = 8;
		style.FrameRounding = 8;
		style.PopupRounding = 8;
		style.ScrollbarRounding = 8;
		style.GrabRounding = 8;
		style.LogSliderDeadzone = 4;
		style.TabRounding = 4;

		// Alignment
		style.WindowTitleAlign = { 0.0, 0.0 };
		style.WindowMenuButtonPosition = ImGuiDir_Right;
		style.ColorButtonPosition = ImGuiDir_Right;


	}

	void Image(const Star<Texture2D>& texture) {
		return Image(texture, ImGui::GetContentRegionAvail());
	}
	void imgui::Image(const Star<Texture2D>& texture, bool ratio) {
		auto size = texture->size();
		auto avail = ImGui::GetContentRegionAvail().x;
		return Image(texture, ImVec2{ avail, size.y * avail / size.x });
	}
	void Image(const Star<Texture2D>& texture, const glm::vec2& size, const glm::vec4& tint) {
		return Image(texture, vec(size), vec(tint));
	}
	void Image(const Star<Texture2D>& texture, const ImVec2& size, const ImVec4& tint) {
		auto img = (void*)(intptr_t)texture->id();
		ImGui::Image(img, size, { 0,1 }, { 1,0 }, tint);
	}

	bool ImageButton(const Star<Texture2D>& texture) {
		return ImageButton(texture, ImGui::GetContentRegionAvail());
	}
	bool ImageButton(const Star<Texture2D>& texture, const glm::vec2& size) {
		return ImageButton(texture, vec(size));
	}
	bool ImageButton(const Star<Texture2D>& texture, const ImVec2& size) {
		auto img = (void*)(intptr_t)texture->id();
		return ImGui::ImageButton(img, size, { 0,1 }, { 1,0 });
	}

}
