#pragma once
#include "npch.h"
#include "base.h"
#include "gui/gui.h"
#include "gui/ext.h"
#include "asset/stock.h"
#include "sol/drop_targets.h"
#include "ecs/component/render.h"

namespace Nova::sol::View {

	struct Sprite : public Base<Component::Sprite> {
		constexpr static cstring title = "Sprite";
		static void render(Component& component) {
			static ImGuiColorEditFlags flags = ImGuiColorEditFlags_InputRGB
				| ImGuiColorEditFlags_AlphaPreviewHalf
				| ImGuiColorEditFlags_AlphaBar
				| ImGuiColorEditFlags_HDR
				| ImGuiColorEditFlags_NoLabel;

			imgui::Text("Colour");
			imgui::SameLine();
			imgui::ColorEdit4("Colour Tint", (float*)&component.colour, flags);

			float width;
			const auto& tex_size = component.texture->size();
			static int texture_option = 0;

			if (imgui::TreeNodeEx("Texture")) {
				width = imgui::GetContentRegionAvailWidth();
				imgui::RadioButton("Base", &texture_option, 0);
				imgui::SameLine();
				imgui::RadioButton("Tint", &texture_option, 1);
				imgui::TreePop();
			} else {
				imgui::SameLine();
				width = imgui::GetFontSize();
			}

			glm::vec4 tint{ 1 };
			if (texture_option == 1)
				tint = component.colour;

			imgui::Image(component.texture, glm::vec2{ width, tex_size.y * width / tex_size.x }, tint);
			Drag::texture(component.texture, ImGuiDragDropFlags_SourceAllowNullID);
			if (imgui::BeginDragDropTarget()) {
				auto payload = imgui::AcceptDragDropPayload(Drag::Drop::texture);
				if (payload) {
					component.texture = *static_cast<decltype(component.texture)*>(payload->Data);
				}
				imgui::EndDragDropTarget();
			}
			if (imgui::BeginPopupContextWindow("TextureContextMenu")) {
				if (imgui::MenuItem("Clear")) {
					component.texture = Resource::Stock::Texture::blank;
				}
				imgui::EndPopup();
			}
		}
	};

}