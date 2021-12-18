#pragma once
#include "npch.h"
#include "base.h"
#include "ecs/entity.h"
#include "../view/base.h"

namespace Nova::sol::Panel {

	class EntityHierarchy : public Base {
	public:
		EntityHierarchy() : Base("Entity Hierarchy") {}
		Nova::ecs::Entity& entity() { return m_entity; }

	protected:
		Nova::ecs::Entity m_entity;

		void gui() override {}

	};

}