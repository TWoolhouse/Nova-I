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
	using cstring = const char*;

	static const std::filesystem::path root_dir = std::filesystem::current_path();
	static constexpr cstring search_path = "asset";
	static constexpr cstring internal_search_paths[] = { "Nova", "Sol" };

	struct Icons {
		const Nova::mlb::vec2 size{ 100, 100 };
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
		Nova::gui::Text(&atype.directory.string().c_str()[root_dir.string().size()]);
		Nova::gui::Separator();

		if (!atype.depth) {
			for (auto& sp : internal_search_paths) {
				Nova::gui::Text((root_dir / sp).string().c_str());
			}
		} else {
			if (Nova::gui::Button("Back")) {
				--atype.depth;
				atype.directory = atype.directory.parent_path();
			}
			Nova::gui::SameLine();
		}
		if (std::filesystem::exists(atype.directory)) {
			auto window_width = Nova::gui::GetContentRegionAvail().x;
			auto element_width = icons.size.x + 2 * Nova::gui::GetStyle().FramePadding.x;
			unsigned int element_limit = (window_width - Nova::gui::GetStyle().ScrollbarSize) / element_width;
			constexpr auto text_lines = 2;

			size_t count = 0;
			for (auto& entry : std::filesystem::directory_iterator(atype.directory)) {
				auto& epath = entry.path();
				//Nova::gui::Text(ename.c_str());

				if (entry.is_directory()) { // Directory
					if (Nova::gui::BeginChild(epath.string().c_str(), { element_width, element_width + text_lines * Nova::gui::GetTextLineHeightWithSpacing() }, true, ImGuiWindowFlags_AlwaysAutoResize || ImGuiWindowFlags_NoScrollbar)) {
						Nova::gui::PushStyleColor(ImGuiCol_Button, Nova::gui::GetColorU32(ImGuiCol_WindowBg));
						auto selected = Nova::gui::ImageButton(icons.lookup(Icons::ID::DIRECTORY), icons.size); // Circumvent short circuit
						Nova::gui::PopStyleColor();
						Nova::gui::TextWrapped(epath.filename().string().c_str());
						if (selected /*|| Nova::gui::IsMouseClicked(ImGuiMouseButton_Left)*/ ) {
							++atype.depth;
							atype.directory = epath;
						}
					} Nova::gui::EndChild();
				} else { // File
					if (Nova::gui::BeginChild(epath.string().c_str(), { element_width, element_width + text_lines * Nova::gui::GetTextLineHeightWithSpacing() }, true, ImGuiWindowFlags_AlwaysAutoResize || ImGuiWindowFlags_NoScrollbar)) {
						Nova::gui::PushStyleColor(ImGuiCol_Button, Nova::gui::GetColorU32(ImGuiCol_WindowBg));
						auto selected = Nova::gui::ImageButton(icons.lookup(atype.icon), icons.size); // Circumvent short circuit
						Nova::gui::PopStyleColor();
						Nova::gui::TextWrapped(epath.filename().string().c_str());
						if (selected /*|| Nova::gui::IsMouseClicked(ImGuiMouseButton_Left)*/ ) {
							atype.selected->active = true;
							atype.selected->path = epath;
							atype.selected->on_select();
						}
					} Nova::gui::EndChild();
				}
				if (++count < element_limit)
					Nova::gui::SameLine();
				else {
					count = 0;
					Nova::gui::NewLine();
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
		if (Nova::gui::BeginTabBar("asset_browser")) {
			for (auto& atype : assets) {
				if (Nova::gui::BeginTabItem(atype.name)) {
					Nova::gui::PopID();
					if (Nova::gui::BeginTable("asset_browser", 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable)) {
						Nova::gui::TableSetupColumn("Preview", ImGuiTableColumnFlags_NoHide);
						Nova::gui::TableSetupColumn("Browser", ImGuiTableColumnFlags_NoHide);

						Nova::gui::TableNextColumn();
						if (Nova::gui::BeginChild("Target")) {
							atype.display_func(atype);
						} Nova::gui::EndChild();

						Nova::gui::TableNextColumn();
						if (Nova::gui::BeginChild("Browser")) {
							explorer(atype);
						} Nova::gui::EndChild();

						Nova::gui::EndTable();
					}
					Nova::gui::PushID(atype.name);
					Nova::gui::EndTabItem();
				}
			}
			Nova::gui::EndTabBar();
		}
	}

	void display_texture(AssetType& atype) {
		auto& active = *static_cast<ASTexture*>(atype.selected);
		if (!active)
			return;
		//Nova::gui::Text(&active->path.string().c_str()[atype.directory.string().size()]);
		auto& name = active.path.filename().string();
		Nova::gui::Text(name.c_str());

		auto size = active.texture->size();
		auto max = Nova::gui::GetContentRegionMax();
		Nova::gui::Image(active.texture, true);
		Editor::Drag::texture(Nova::Asset<Nova::Texture2D>{
			""_ns, active.texture, { active.path.string(), {} }
		}, ImGuiDragDropFlags_SourceAllowNullID);
	}
	void display_shader(AssetType& atype) {
		auto& active = *static_cast<AssetSelected*>(atype.selected);
		if (!active)
			return;
		Nova::gui::Text(active.path.filename().string().c_str());
	}

}
