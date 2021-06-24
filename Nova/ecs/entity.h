#pragma once
#include "npch.h"
#include "ecs.h"
#include "world.h"

namespace Nova::ecs {
	class Entity : public entt::handle {
	public:
		using Type = entt::entity;
		Entity() : entt::handle() {}
		Entity(Registry& registry, const Type& entity) : entt::handle(registry, entity) {}
		Entity(World& world, const Type& entity) : entt::handle(world.registry, entity) {}
		Entity(const Star<World>& world, const Type& entity) : entt::handle(world->registry, entity) {}
		Registry& registry() const noexcept { return *entt::handle::registry(); }
		const Type entity() const noexcept { return entt::handle::entity(); }
		operator entt::entity() const noexcept { return entity(); };
		operator unsigned int() const noexcept { return static_cast<unsigned int>(entity()); };
	};
}
