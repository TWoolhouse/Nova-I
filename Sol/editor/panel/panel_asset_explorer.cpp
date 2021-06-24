#include "spch.h"
#include "asset_explorer.h"
#include <filesystem>

namespace Sol::Panel {

	void display_texture();
	void display_shader();

	typedef void (*DisplayFunc)(void);
	using cstring = const char*;
	static constexpr cstring search_paths[] = {
	"Nova/", "asset/"
	};
	static constexpr std::tuple<cstring, cstring, DisplayFunc> asset_types[] = {
		{ "Textures", "texture", &display_texture },
		{ "Shaders", "shader", &display_shader },
	};

	void explorer(const char* asset_type) {
		Nova::gui::Text("Nice!");
	}

	void AssetExplorer::gui() {
		if (Nova::gui::BeginTabBar("asset_browser")) {
			for (auto& [name, type, display_func] : asset_types) {
				if (Nova::gui::BeginTabItem(name)) {
					Nova::gui::PopID();
					if (Nova::gui::BeginTable("asset_browser", 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable)) {
						Nova::gui::TableSetupColumn("Preview", ImGuiTableColumnFlags_NoHide);
						Nova::gui::TableSetupColumn("Browser", ImGuiTableColumnFlags_NoHide);

						Nova::gui::TableNextColumn();
						display_func();

						Nova::gui::TableNextColumn();
						if (Nova::gui::BeginChild("Browser")) {
							explorer(type);
						} Nova::gui::EndChild();

						Nova::gui::EndTable();
					}
					Nova::gui::PushID(name);
					Nova::gui::EndTabItem();
				}
			}
			Nova::gui::EndTabBar();
		}
	}

	void display_texture() {
		Nova::gui::Text("Texture");
	}
	void display_shader() {
		Nova::gui::Text("Shader");
	}

}