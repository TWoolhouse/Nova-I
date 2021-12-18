#pragma once
#include "gui.h"
#include "render/texture.h"

namespace Nova::imgui {

	inline ImVec2 vec(const glm::vec2& v) {
		return { v.x, v.y };
	}
	inline ImVec4 vec(const glm::vec4& v) {
		return { v.x, v.y, v.z, v.w };
	}

	NOVA_API void Image(const Star<Texture2D>& texture);
	NOVA_API void Image(const Star<Texture2D>& texture, bool ratio);
	NOVA_API void Image(const Star<Texture2D>& texture, const glm::vec2& size, const glm::vec4& tint = { 1, 1, 1, 1 });
	NOVA_API void Image(const Star<Texture2D>& texture, const ImVec2& size, const ImVec4& tint = { 1, 1, 1, 1 });

	NOVA_API bool ImageButton(const Star<Texture2D>& texture);
	NOVA_API bool ImageButton(const Star<Texture2D>& texture, const glm::vec2& size);
	NOVA_API bool ImageButton(const Star<Texture2D>& texture, const ImVec2& size);

	inline ImGuiID BeginDockspace() {
		return Nova::imgui::DockSpaceOverViewport(Nova::imgui::GetMainViewport());
	}
	inline void EndDockspace() {}

}