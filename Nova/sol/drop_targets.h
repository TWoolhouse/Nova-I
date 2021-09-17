#pragma once
#include "gui/gui.h"
#include "asset/type.h"
#include "render/texture.h"

namespace Nova::sol::Drag {
	namespace Drop {
		constexpr cstring shader = "drop_shader";
		constexpr cstring texture = "drop_texture";
	}

	void texture(const Asset<Texture2D>& texture, ImGuiDragDropFlags flags = ImGuiDragDropFlags_None);

}