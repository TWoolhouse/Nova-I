#pragma once
#include "gui.h"
#include "render/texture.h"

namespace Nova::imgui {

	NOVA_API void Image(const Star<Texture2D>& texture);
	NOVA_API void Image(const Star<Texture2D>& texture, bool ratio);
	NOVA_API void Image(const Star<Texture2D>& texture, const glm::vec2& size, const glm::vec4& tint = { 1, 1, 1, 1 });
	NOVA_API void Image(const Star<Texture2D>& texture, const ImVec2& size, const ImVec4& tint = { 1, 1, 1, 1 });

	NOVA_API bool ImageButton(const Star<Texture2D>& texture);
	NOVA_API bool ImageButton(const Star<Texture2D>& texture, const glm::vec2& size);
	NOVA_API bool ImageButton(const Star<Texture2D>& texture, const ImVec2& size);

}