#pragma once
#include "npch.h"
#include "util/macro.h"
#include "ecs/component.h"

#define SolView(view) namespace Nova::sol::View { NovaVarTypeList(Pack, view) }

namespace Nova::sol::View {
	NovaVarTypeListNew(Pack, 256)

	template<typename C>
	class Base {
		static_assert(std::is_base_of<ecs::Component, C>::value, "C must be subclass of Component");
	public:
		using Component = C;
		constexpr static cstring title = "Null";
		static void render(Component&) { nova_assert(false, "Empty View being used"); }
	};

}