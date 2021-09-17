#pragma once
#include "npch.h"

#include <entt/entt.hpp>

namespace Nova {
	namespace ecs {
		using Registry = entt::registry;
		namespace Components{ }
	}
	namespace entt {
		using namespace ::entt;
	}
	namespace Component {
		using namespace ecs::Components;
	}
}