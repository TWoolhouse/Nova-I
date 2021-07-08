#pragma once
#include "view.h"
#include "editor/drop_targets.h"

namespace Sol::View {

	struct Name : public View<Nova::Component::Name> {
		constexpr static cstring title = "Name";
		static void render(Component& component) {
			Nova::imgui::Text("Entity");
			Nova::imgui::SameLine();
			Nova::imgui::InputText("##Entity", &component.name);
		}
	};

	struct Transform : public View<Nova::Component::Transform> {
		constexpr static cstring title = "Transform";
		static void render(Component& component) {
			render_single("Position", "##p", component.pos);
			auto deg_rot = glm::degrees(component.rot);
			render_single("Rotation", "##r", deg_rot, 0.5);
			component.rot = glm::radians(deg_rot);
			render_single("Scale", "##s", component.scl);
		}
		static void render_single(cstring name, cstring tag, Nova::glm::vec3& vec, float speed = 0.1) {
			if (Nova::imgui::TreeNode(name)) {
				Nova::imgui::Text("X");
				Nova::imgui::SameLine();
				Nova::imgui::DragFloat("##x", &vec.x, speed, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				Nova::imgui::Text("Y");
				Nova::imgui::SameLine();
				Nova::imgui::DragFloat("##y", &vec.y, speed, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				Nova::imgui::Text("Z");
				Nova::imgui::SameLine();
				Nova::imgui::DragFloat("##z", &vec.z, speed, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				Nova::imgui::TreePop();
			} else {
				Nova::imgui::Indent();
				Nova::imgui::DragFloat3(tag, (float*)&vec, speed, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				Nova::imgui::Unindent();
			}
		}
	};

	struct Sprite : public View<Nova::Component::Sprite> {
		constexpr static cstring title = "Sprite";
		static void render(Component& component) {
			static ImGuiColorEditFlags flags = ImGuiColorEditFlags_InputRGB
				| ImGuiColorEditFlags_AlphaPreviewHalf
				| ImGuiColorEditFlags_AlphaBar
				| ImGuiColorEditFlags_HDR
				| ImGuiColorEditFlags_NoLabel;

			Nova::imgui::Text("Colour");
			Nova::imgui::SameLine();
			Nova::imgui::ColorEdit4("Colour Tint", (float*)&component.colour, flags);

			float width;
			const auto& tex_size = component.texture->size();
			static int texture_option = 0;

			if (Nova::imgui::TreeNodeEx("Texture")) {
				width = Nova::imgui::GetContentRegionAvailWidth();
				Nova::imgui::RadioButton("Base", &texture_option, 0);
				Nova::imgui::SameLine();
				Nova::imgui::RadioButton("Tint", &texture_option, 1);
				Nova::imgui::TreePop();
			} else {
				Nova::imgui::SameLine();
				width = Nova::imgui::GetFontSize();
			}

			Nova::glm::vec4 tint{1};
			if (texture_option == 1)
				tint = component.colour;

			Nova::imgui::Image(component.texture, Nova::glm::vec2{ width, tex_size.y * width / tex_size.x }, tint);
			Editor::Drag::texture(component.texture, ImGuiDragDropFlags_SourceAllowNullID);
			if (Nova::imgui::BeginDragDropTarget()) {
				auto payload = Nova::imgui::AcceptDragDropPayload(Editor::Drag::Drop::texture);
				if (payload) {
					component.texture = *static_cast<decltype(component.texture)*>(payload->Data);
				}
				Nova::imgui::EndDragDropTarget();
			}
			if (Nova::imgui::BeginPopupContextWindow("TextureContextMenu")) {
				if (Nova::imgui::MenuItem("Clear")) {
					component.texture = Nova::Resource::Stock::Texture::blank;
				}
				Nova::imgui::EndPopup();
			}
		}
	};

}

SolView(Sol::View::Name)
SolView(Sol::View::Transform)
SolView(Sol::View::Sprite)