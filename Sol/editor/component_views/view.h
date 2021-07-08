#pragma once
#include "spch.h"
#include <nova.h>

#define SolView(view) namespace Sol::View { NovaVarTypeList(Pack, view) }

namespace Sol::View {
	NovaVarTypeListNew(Pack, 256)

	template<typename C>
	class View {
		static_assert(std::is_base_of<Nova::ecs::Component, C>::value, "C must be subclass of Component");
	public:
		using Component = C;
		constexpr static cstring title = "Null";
		static void render(Component&) { nova_assert(false, "Empty View being used"); }
	};

}