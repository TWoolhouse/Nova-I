#include "spch.h"
#include "drop_targets.h"

namespace Sol::Editor::Drag {

	void texture(const Nova::Asset<Nova::Texture2D>& texture, ImGuiDragDropFlags flags) {
		if (Nova::imgui::BeginDragDropSource(flags)) {
			Nova::imgui::SetDragDropPayload(Drop::texture, static_cast<const void*>(&texture), sizeof(decltype(texture)));
			Nova::imgui::Image(texture, Nova::glm::vec2{ 100, 100 });
			Nova::imgui::EndDragDropSource();
		}
	}
}