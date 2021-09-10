#include "spch.h"
#include <nova.h>
#include "editor/panels.h"
#include <type_traits>

namespace Sol::Panel {
	std::unordered_map<std::string_view, Panel*> generate() {
		std::vector<Panel*> panels = {
			new Settings(),
			new Stats(),
			new SceneHierarchy(),
			new AssetExplorer(),
		};

		std::unordered_map<std::string_view, Panel*> map;
		map.reserve(panels.size());
		for (auto& panel : panels) {
			map[panel->name()] = panel;
		}
		return map;
	}

	static std::unordered_map<std::string_view, Sol::Panel::Panel*> panels = generate();
	std::unordered_map<std::string_view, Panel*>& map() { return panels; }
	void map_add(Panel* panel) {
		panels[panel->name()] = panel;
	}

}