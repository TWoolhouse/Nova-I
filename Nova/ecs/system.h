#pragma once
#include "npch.h"
#include "ecs.h"
#include "event/event.h"
 #include "world.h"

namespace Nova::ecs {

	class System {
	public:
		System(World& world) : world(world), reg(world.registry) {}
		virtual ~System() {}

		virtual void update() {}
		virtual void event(Event::Event& event) {}

	protected:
		World& world;
		Registry& reg;
	};

}