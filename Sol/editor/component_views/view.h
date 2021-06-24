#pragma once
#include "spch.h"
#include <nova.h>

namespace Sol::View {

	template<typename C>
	class View {
		static_assert(std::is_base_of<Nova::ecs::Component, C>::value, "C must be subclass of Component");
	public:
		using Component = C;
		constexpr static const char* title = "Null";
		static void render(Component&) { nova_assert(false, "Empty View being used"); }
	};

}