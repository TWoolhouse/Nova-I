#pragma once
#include "view.h"

namespace Sol::View {

	struct Name : public View<Nova::Component::Name> {
		constexpr static const char* title = "Name";
		static void render(Component& component) {
			Nova::gui::Text("Entity");
			Nova::gui::SameLine();
			Nova::gui::InputText("##Entity", &component.name);
		}
	};

	struct Transform : public View<Nova::Component::Transform> {
		constexpr static const char* title = "Transform";
		static void render(Component& component) {
			render_single("Position", "##p", component.pos);
			render_single("Rotation", "##r", component.rot);
			render_single("Scale", "##s", component.scl);
		}
		static void render_single(const char* name, const char* tag, Nova::mlb::vec3& vec) {
			if (Nova::gui::TreeNode(name)) {
				Nova::gui::Text("X");
				Nova::gui::SameLine();
				Nova::gui::DragFloat("##x", &vec.x, 0.1, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				Nova::gui::Text("Y");
				Nova::gui::SameLine();
				Nova::gui::DragFloat("##y", &vec.y, 0.1, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				Nova::gui::Text("Z");
				Nova::gui::SameLine();
				Nova::gui::DragFloat("##z", &vec.z, 0.1, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				Nova::gui::TreePop();
			} else {
				Nova::gui::Indent();
				Nova::gui::DragFloat3(tag, (float*)&vec, 0.1, 0, 0, nullptr, ImGuiSliderFlags_NoRoundToFormat);
				Nova::gui::Unindent();
			}
		}
	};

	struct Sprite : public View<Nova::Component::Sprite> {
		constexpr static const char* title = "Sprite";
		static void render(Component& component) {
			static ImGuiColorEditFlags flags = ImGuiColorEditFlags_InputRGB
				| ImGuiColorEditFlags_AlphaPreviewHalf
				| ImGuiColorEditFlags_AlphaBar
				| ImGuiColorEditFlags_HDR
				| ImGuiColorEditFlags_NoLabel;

			Nova::gui::Text("Colour");
			Nova::gui::SameLine();
			Nova::gui::ColorEdit4("Colour Tint", (float*)&component.colour, flags);

			float width;
			const auto& tex_size = component.texture->size();
			static int texture_option = 0;

			if (Nova::gui::TreeNodeEx("Texture")) {
				width = Nova::gui::GetContentRegionAvailWidth();
				Nova::gui::RadioButton("Base", &texture_option, 0);
				Nova::gui::SameLine();
				Nova::gui::RadioButton("Tint", &texture_option, 1);
				Nova::gui::TreePop();
			} else {
				Nova::gui::SameLine();
				width = Nova::gui::GetFontSize();
			}

			Nova::mlb::vec4 tint{1};
			if (texture_option == 1)
				tint = component.colour;

			Nova::gui::Image(component.texture, Nova::mlb::vec2{ width, tex_size.y * width / tex_size.x }, tint);
		}
	};

}