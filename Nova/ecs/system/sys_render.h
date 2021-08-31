#pragma once
#include "npch.h"
#include "../system.h"
#include "../component/transform.h"
#include "../component/render.h"
#include "render/draw.h"
#include "render/camera.h"

namespace Nova::ecs::sys {

	class Render : public System {
	public:
		Render(World& world, Nova::Render::Camera* camera) : System(world), camera(camera) {}
		~Render() {}
		void update() override {
			Nova::Render::Draw(camera);
			for (auto&& [entity, transform, sprite] : reg.group<Components::Transform, Components::Sprite>().each()) {
				Nova::Draw::Quad(transform.global(Entity{ reg, entity }).transform(), sprite.colour, sprite.texture);
			}
			Nova::Render::Draw();
		}
		Nova::Render::Camera* camera;
	};

}