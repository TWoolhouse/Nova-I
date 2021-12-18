#pragma once
#include "npch.h"
#include "util/macro.h"
#include "ecs/component.h"

#define SolView(view) namespace Nova::sol::View { NovaVarTypeList(Pack, view) }

namespace Nova::sol::View {
	NovaVarTypeListNew(Pack, 256)

	template<typename C>
		requires std::is_base_of_v<Nova::ecs::Component, C>
	class Base {
	public:
		using Component = C;
		constexpr static cstring title = "Null";
		static void render(Component&) { nova_assert(false, "Empty View being used"); }
	};

	template<typename V> concept Viewable = (requires (V v) {
		V::Component;
	}) && std::is_base_of_v<Base<typename V::Component>, V>;

}