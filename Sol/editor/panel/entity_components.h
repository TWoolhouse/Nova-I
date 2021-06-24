#pragma once
#include "spch.h"
#include <nova.h>
#include "core/panel.h"

#include "scene_hierarchy.h"

namespace Sol::Panel {
	class EntityComponents : public Panel {
	public:
		EntityComponents(SceneHierarchy& sh) : Panel("Entity"), hierarchy(sh) {}
	protected:
		virtual void gui() override;
		SceneHierarchy& hierarchy;
	};
}
