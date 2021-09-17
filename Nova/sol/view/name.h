#pragma once
#include "npch.h"
#include "base.h"
#include "gui/gui.h"
#include "ecs/component/name.h"

namespace Nova::sol::View {

	struct Name : public Base<Component::Name> {
		constexpr static cstring title = "Name";
		static void render(Component& component) {
			Nova::imgui::Text("Entity");
			Nova::imgui::SameLine();
			Nova::imgui::InputText("##Entity", &component.name);
		}
	};

}

SolView(Nova::sol::View::Name)
