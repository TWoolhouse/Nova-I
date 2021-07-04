#pragma once
#include <nova.h>

namespace Sol::Editor::Drag {
	namespace Drop {
		constexpr auto texture = "drop_texture";
		constexpr auto shader = "drop_shader";
	}

	void texture(const Nova::Asset<Nova::Texture2D>& texture, ImGuiDragDropFlags flags = ImGuiDragDropFlags_None);

}