#pragma once
#include "spch.h"
#include <nova.h>
#include "ion.h"

namespace Sol {

	constexpr cstring win_name = "New Game Solution";
	ImGuiID pid;

	const ImGuiID make_id() {
		pid = Nova::imgui::GetID(win_name);
		return pid;
	}

	void Ion::gui() {
		static const ImGuiID id = make_id();
		if (Nova::imgui::BeginPopupModal(win_name, 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize)) {
			static std::string sln_name;
			bool done = Nova::imgui::InputTextWithHint("##name", "Project Name", &sln_name, ImGuiInputTextFlags_EnterReturnsTrue);
			if (Nova::imgui::Button("Cancel")) Nova::imgui::CloseCurrentPopup();
			Nova::imgui::SameLine();
			if ((done || Nova::imgui::Button("Create")) && !sln_name.empty()) {
				Nova::imgui::CloseCurrentPopup();
				std::cout << "Create New Solution: " << sln_name << std::endl;
				auto sln = Ion(sln_name);
				sln_name.clear();
			}
			Nova::imgui::EndPopup();
		}
	}
	void Ion::gui_open() {
		Nova::imgui::OpenPopup(pid);
	}
}