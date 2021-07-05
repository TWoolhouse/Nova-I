#include "spch.h"
#include "asset_explorer.h"
#include <filesystem>
#include <nova.h>
#include "editor/drop_targets.h"

namespace Sol::Panel {

	struct AssetType;

	void display_texture(AssetType&);
	void display_shader(AssetType&);

	typedef void (*DisplayFunc)(AssetType&);

	static const std::filesystem::path root_dir = std::filesystem::current_path();
	static constexpr cstring search_path = "asset";
	static constexpr cstring internal_search_paths[] = { "Nova", "Sol" };

	struct Icons {
		const Nova::glm::vec2 size{ 100, 100 };
		Nova::Star<Nova::Texture2D> file;
		Nova::Star<Nova::Texture2D> image;
		Nova::Star<Nova::Texture2D> directory;

		enum class ID : unsigned char {
			FILE = 0,
			IMAGE, DIRECTORY
		};

		void default(const Nova::Star<Nova::Texture2D>& texture) {
			file = texture;
			directory = texture;
			image = texture;
		}
		Nova::Star<Nova::Texture2D>& lookup(const ID& id) {
			switch (id) {
			case ID::IMAGE:	return image;
			case ID::FILE:	return file;
			case ID::DIRECTORY:	return directory;
			default:	return lookup(ID::FILE);
			}
		}
	} icons;

	struct AssetSelected {
		bool active = false;
		std::filesystem::path path;
		AssetSelected(const std::filesystem::path& path) : path(path) {}
		virtual void on_select() {}
		operator bool() const { return active; }
	};

	struct AssetType {
		const cstring name, inner;
		const DisplayFunc display_func;
		std::filesystem::path base, directory;
		unsigned int depth;
		const Icons::ID icon;
		AssetSelected* selected;

		template<typename Asset>
		AssetType(const cstring& name, const cstring& inner, const DisplayFunc& display, const Nova::var::pack<Asset>&, const Icons::ID& icon_id = Icons::ID::FILE)
			: name(name), inner(inner), display_func(display),
			base(root_dir / search_path / inner), directory(base), depth(0),
			icon(icon_id),
			selected(new Asset(directory)) { static_assert(std::is_base_of_v<AssetSelected, Asset>, "Selected Asset Type not correct Base"); }
		~AssetType() { delete selected; }
	};

	struct ASTexture : public AssetSelected {
		Nova::Star<Nova::Texture2D> texture;
		ASTexture(const std::filesystem::path& path) : AssetSelected(path) {}
		virtual void on_select() override {
			texture = Nova::Texture2D::Create(path.string());
		}
	};

	static AssetType assets[] = {
		{ "Textures", "texture", &display_texture, Nova::var::pack<ASTexture>{}, Icons::ID::IMAGE },
		{ "Shaders", "shader", &display_shader, Nova::var::pack<AssetSelected>{} },
	};

	void explorer(AssetType& atype) {
		Nova::imgui::Text(&atype.directory.string().c_str()[root_dir.string().size()]);
		Nova::imgui::Separator();

		if (!atype.depth) {
			for (auto& sp : internal_search_paths) {
				Nova::imgui::Text((root_dir / sp).string().c_str());
			}
		} else {
			if (Nova::imgui::Button("Back")) {
				--atype.depth;
				atype.directory = atype.directory.parent_path();
			}
			Nova::imgui::SameLine();
		}
		if (std::filesystem::exists(atype.directory)) {
			auto window_width = Nova::imgui::GetContentRegionAvail().x;
			auto element_width = icons.size.x + 2 * Nova::imgui::GetStyle().FramePadding.x;
			unsigned int element_limit = (window_width - Nova::imgui::GetStyle().ScrollbarSize) / element_width;
			constexpr auto text_lines = 2;

			size_t count = 0;
			for (auto& entry : std::filesystem::directory_iterator(atype.directory)) {
				auto& epath = entry.path();
				//Nova::gui::Text(ename.c_str());

				if (entry.is_directory()) { // Directory
					if (Nova::imgui::BeginChild(epath.string().c_str(), { element_width, element_width + text_lines * Nova::imgui::GetTextLineHeightWithSpacing() }, true, ImGuiWindowFlags_AlwaysAutoResize || ImGuiWindowFlags_NoScrollbar)) {
						Nova::imgui::PushStyleColor(ImGuiCol_Button, Nova::imgui::GetColorU32(ImGuiCol_WindowBg));
						auto selected = Nova::imgui::ImageButton(icons.lookup(Icons::ID::DIRECTORY), icons.size); // Circumvent short circuit
						Nova::imgui::PopStyleColor();
						Nova::imgui::TextWrapped(epath.filename().string().c_str());
						if (selected /*|| Nova::gui::IsMouseClicked(ImGuiMouseButton_Left)*/ ) {
							++atype.depth;
							atype.directory = epath;
						}
					} Nova::imgui::EndChild();
				} else { // File
					if (Nova::imgui::BeginChild(epath.string().c_str(), { element_width, element_width + text_lines * Nova::imgui::GetTextLineHeightWithSpacing() }, true, ImGuiWindowFlags_AlwaysAutoResize || ImGuiWindowFlags_NoScrollbar)) {
						Nova::imgui::PushStyleColor(ImGuiCol_Button, Nova::imgui::GetColorU32(ImGuiCol_WindowBg));
						auto selected = Nova::imgui::ImageButton(icons.lookup(atype.icon), icons.size); // Circumvent short circuit
						Nova::imgui::PopStyleColor();
						Nova::imgui::TextWrapped(epath.filename().string().c_str());
						if (selected /*|| Nova::gui::IsMouseClicked(ImGuiMouseButton_Left)*/ ) {
							atype.selected->active = true;
							atype.selected->path = epath;
							atype.selected->on_select();
						}
					} Nova::imgui::EndChild();
				}
				if (++count < element_limit)
					Nova::imgui::SameLine();
				else {
					count = 0;
					Nova::imgui::NewLine();
				}
			}
		}

	}

	AssetExplorer::AssetExplorer() : Panel("Asset Explorer", ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse) {
		icons.default(Nova::Texture2D::Create("Sol/texture/icon/file.png"));
		icons.directory = Nova::Texture2D::Create("Sol/texture/icon/folder.png");
		icons.image = Nova::Texture2D::Create("Sol/texture/icon/image.png");
	}

	void AssetExplorer::gui() {
		if (Nova::imgui::BeginTabBar("asset_browser")) {
			for (auto& atype : assets) {
				if (Nova::imgui::BeginTabItem(atype.name)) {
					Nova::imgui::PopID();
					if (Nova::imgui::BeginTable("asset_browser", 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable)) {
						Nova::imgui::TableSetupColumn("Preview", ImGuiTableColumnFlags_NoHide);
						Nova::imgui::TableSetupColumn("Browser", ImGuiTableColumnFlags_NoHide);

						Nova::imgui::TableNextColumn();
						if (Nova::imgui::BeginChild("Target")) {
							atype.display_func(atype);
						} Nova::imgui::EndChild();

						Nova::imgui::TableNextColumn();
						if (Nova::imgui::BeginChild("Browser")) {
							explorer(atype);
						} Nova::imgui::EndChild();

						Nova::imgui::EndTable();
					}
					Nova::imgui::PushID(atype.name);
					Nova::imgui::EndTabItem();
				}
			}
			Nova::imgui::EndTabBar();
		}
	}

	void display_texture(AssetType& atype) {
		auto& active = *static_cast<ASTexture*>(atype.selected);
		if (!active)
			return;
		//Nova::gui::Text(&active->path.string().c_str()[atype.directory.string().size()]);
		auto& name = active.path.filename().string();
		Nova::imgui::Text(name.c_str());

		auto size = active.texture->size();
		auto max = Nova::imgui::GetContentRegionMax();
		Nova::imgui::Image(active.texture, true);
		Editor::Drag::texture(Nova::Asset<Nova::Texture2D>{
			""_ns, active.texture, { active.path.string(), {} }
		}, ImGuiDragDropFlags_SourceAllowNullID);
	}
	void display_shader(AssetType& atype) {
		auto& active = *static_cast<AssetSelected*>(atype.selected);
		if (!active)
			return;
		Nova::imgui::Text(active.path.filename().string().c_str());
	}

}
