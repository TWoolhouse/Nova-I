#pragma once
#include "spch.h"
#include "panel/settings.h"
#include "panel/stats.h"
#include "panel/scene_hierarchy.h"
#include "panel/entity_components.h"
#include "panel/asset_explorer.h"

namespace Sol::Panel {
	std::unordered_map<std::string, Panel*> generate();
}