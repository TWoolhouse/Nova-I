#include "spch.h"
#include <nova.h>
#include "editor/panels.h"

namespace Sol::Panel {
	std::unordered_map<std::string_view, Panel*> generate() {
		auto sh = new SceneHierarchy();
		std::vector<Panel*> panels = {
			new Settings(),
			new Stats(),
			sh,
			new EntityComponents(*sh),
			new AssetExplorer(),
		};
	
		std::unordered_map<std::string_view, Panel*> map;
		map.reserve(panels.size());
		for (auto& panel : panels) {
			map[panel->name()] = panel;
		}
		return map;
	}

}