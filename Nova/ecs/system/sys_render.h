#pragma once
#include "npch.h"
#include "../system.h"
#include "../component/transform.h"
#include "../component/render.h"
#include "render/draw.h"

namespace Nova::ecs::sys {

	class Render : public System {
	public:
		Render(World& world) : System(world) {}
		~Render() {}
		void update() override {
			for (auto&& [entity, transform, sprite] : reg.group<Components::Transform, Components::Sprite>().each()) {
				Nova::Draw::Quad(transform.global(Entity{ reg, entity }).transform(), sprite.colour, sprite.texture);
			}
		}
	};

}