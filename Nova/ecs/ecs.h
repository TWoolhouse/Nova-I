#pragma once
#include "npch.h"

#ifndef NOVA_EXPORT
#include "dep/entt/entt/entt.hpp"
#else
#include <entt/entt.hpp>
#endif // NOVA_EXPORT

namespace Nova {
	namespace ecs {
		using Registry = entt::registry;
	}
	namespace entt {
		using namespace ::entt;
	}
}