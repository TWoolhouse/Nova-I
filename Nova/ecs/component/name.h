#pragma once
#include "npch.h"
#include "../component.h"
#include "serial/cereal.h"

namespace Nova::ecs::Components {

	struct Name : public Component {
		std::string name = "Name";

		Name() = default;
		Name(const Name&) = default;
		Name(const std::string& name) : name(name) {}

		operator std::string& () { return name; }
		operator const std::string& () const { return name; }

		NovaCerealise { serialise(name); }
	};

}