#pragma once
#include "npch.h"
#include "../component.h"
#include "transform.h"

#include "phys/lib.h"
#include "render/texture.h"

namespace Nova::ecs::Components {

	struct Sprite : public Component {
		mlb::vec4 colour{ 1.0f };
		Star<Texture2D> texture = RenderState::Get().blank_texture;

		Sprite() = default;
		Sprite(const Sprite&) = default;
		Sprite(const mlb::vec4& colour) : colour(colour) {}
	};

}