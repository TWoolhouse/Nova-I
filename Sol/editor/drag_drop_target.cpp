#include "spch.h"
#include "drop_targets.h"

namespace Sol::Editor::Drag {

	void texture(const Nova::Asset<Nova::Texture2D>& texture, ImGuiDragDropFlags flags) {
		if (Nova::gui::BeginDragDropSource(flags)) {
			Nova::gui::SetDragDropPayload(Drop::texture, static_cast<const void*>(&texture), sizeof(decltype(texture)));
			Nova::gui::Image(texture, Nova::mlb::vec2{ 100, 100 });
			Nova::gui::EndDragDropSource();
		}
	}
}