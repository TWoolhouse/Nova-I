#pragma once
#include "npch.h"
#include "../component.h"
#include "serial/cereal.h"
#include "transform.h"

#include "phys/lib.h"
#include "render/texture.h"
#include "asset/type.h"

namespace Nova::ecs::Components {

	struct Sprite : public Component {
		glm::vec4 colour{ 1.0f };
		Asset<Texture2D> texture = Resource::Stock::Texture::blank;

		Sprite() = default;
		Sprite(Sprite&&) = default;
		Sprite& operator=(Sprite&&) = default;
		Sprite(const glm::vec4& colour) : colour(colour) {}

		NovaCerealise{ serialise(colour); }
	};

}