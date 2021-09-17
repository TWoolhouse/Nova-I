#pragma once
#include "npch.h"
#include "base.h"
#include "ecs/component/transform.h"
#include "gui/gui.h"

namespace Nova::sol::View {

	struct Transform : public Base<Component::Transform> {
		constexpr static cstring title = "Transform";
		static void render(Component& component) {
			render_single("Position", "##p", component.pos);
			auto deg_rot = glm::degrees(component.rot);
			render_single("Rotation", "##r", deg_rot, 0.5);
			component.rot = glm::radians(deg_rot);
			render_single("Scale", "##s", component.scl);
		}
		static void render_single(cstring name, cstring tag, glm::vec3& vec, float speed = 0.1) {
			if (imgui::TreeNode(name)) {
				imgui::Text("X");
				imgui::SameLine();
				imgui::DragFloat("##x", &vec.x, speed, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				imgui::Text("Y");
				imgui::SameLine();
				imgui::DragFloat("##y", &vec.y, speed, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				imgui::Text("Z");
				imgui::SameLine();
				imgui::DragFloat("##z", &vec.z, speed, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				imgui::TreePop();
			} else {
				Nova::imgui::Indent();
				Nova::imgui::DragFloat3(tag, (float*)&vec, speed, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				Nova::imgui::Unindent();
			}
		}
	};

}

SolView(Nova::sol::View::Transform)
