#include "npch.h"
#include "gui/ext.h"
#include "drop_targets.h"

namespace Nova::sol::Drag {

	void texture(const Asset<Texture2D>& texture, ImGuiDragDropFlags flags) {
		if (Nova::imgui::BeginDragDropSource(flags)) {
			Nova::imgui::SetDragDropPayload(Drop::texture, static_cast<const void*>(&texture), sizeof(decltype(texture)));
			Nova::imgui::Image(texture, glm::vec2{ 100, 100 });
			Nova::imgui::EndDragDropSource();
		}
	}
}