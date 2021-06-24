#include "npch.h"
#include "ecs.h"
#include "entity.h"
#include "component.h"
#include "system.h"
#include "world.h"

namespace Nova::ecs {

	Star<World> World::Create() {
		return std::make_shared<World>();
	}

	World::World() : registry() {}
	World::~World() {
		for (auto& sys : m_systems) {
			delete sys;
		}
	}

	void World::update() {
		for (auto& sys : m_systems) {
			sys->update();
		}
	}
	void World::event(Event::Event& event) {
		for (auto it = m_systems.rbegin(); it < m_systems.crend(); ++it) {
			if (event.done)
				break;
			(*it)->event(event);
		}
	}

	Entity World::instantiate() {
		return Entity(registry, registry.create());
	}

}