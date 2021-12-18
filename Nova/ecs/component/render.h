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
		Sprite(Sprite&&) noexcept = default;
		Sprite& operator=(Sprite&&) noexcept = default;
		Sprite(const glm::vec4& colour) : colour(colour) {}
		Sprite(const Asset<Texture2D>& texture) : texture(texture) {}
		Sprite(const glm::vec4& colour, const Asset<Texture2D>& texture) : colour(colour), texture(texture) {}
		Sprite(const Nova::Star<Texture2D>& texture) : texture(texture) {}
		Sprite(const glm::vec4& colour, const Nova::Star<Texture2D>& texture) : colour(colour), texture(texture) {}
	protected:
		NovaCerealise{ serialise(colour); }
	};

}