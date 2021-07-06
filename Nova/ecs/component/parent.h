#pragma once
#include "npch.h"
#include "../component.h"
#include "serial/cereal.h"
#include "../entity.h"

namespace Nova::ecs::Components {

	struct Parent : public Component {
		Entity::Type entity{entt::null};

		Parent() = default;
		Parent(const Parent&) = default;
		Parent(const Entity& parent) : entity(parent) {}

		operator Entity::Type& () { return entity; }
		operator const Entity::Type& () const { return entity; }

		operator bool() { return entity != entt::null; }
		operator const bool() const { return entity != entt::null; }

		NovaCerealise{ serialise(entity); }
	};

}