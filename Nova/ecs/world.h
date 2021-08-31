#pragma once
#include "npch.h"
#include "ecs.h"
#include "event/event.h"
#include "component.h"

namespace Nova::ecs {

	class Entity;
	class System;

	class NOVA_API World {
		friend class System;
	public:
		Registry registry;
		static Star<World> Create();

		World();
		~World();

		void update();
		void event(Event::Event& event);

		template<typename S, typename ...Args>
		S& system(Args... args) {
			static_assert(std::is_base_of_v<System, S>, "Typename S is not subclass of System");
			return *static_cast<S*>(m_systems.emplace_back(new S(*this, args...)));
		}
		template<typename S>
		S& system_state(bool enable) {
			static_assert(std::is_base_of_v<System, S>, "Typename S is not subclass of System");
			nova_assert(false, "TODO");
		}

		Entity instantiate();

	protected:
		std::vector<System*> m_systems;
	};

}