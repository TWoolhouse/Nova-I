#include "spch.h"
#include <nova.h>
#include "entity_components.h"

#include "editor/views.h"

namespace Sol::Panel {

	constexpr View::Views PACK{};

	template<typename V>
	void context_menu(Nova::ecs::Entity& entity) {
		// TEMPORARY AS MENU IS EMPTY FOR THEM
		if constexpr ((std::is_same_v<V, View::Name> || std::is_same_v<V, View::Transform>))
			return; // TEMPORARY AS MENU IS EMPTY FOR THEM

		static constexpr auto cname = "CompCntxtMenu";
		if (Nova::imgui::IsItemHovered()) {
			constexpr auto button_str = "...";
			Nova::imgui::SameLine(Nova::imgui::GetContentRegionAvail().x - Nova::imgui::CalcTextSize(button_str).x);
			if (Nova::imgui::Button(button_str) || Nova::imgui::IsItemClicked()) {
				Nova::imgui::OpenPopup(cname);
			}
		}
		if (Nova::imgui::BeginPopup(cname)) {
			if constexpr (!(std::is_same_v<V, View::Name> || std::is_same_v<V, View::Transform>))
			if (Nova::imgui::MenuItem("Delete", "Del") || Nova::imgui::IsKeyPressed(Nova::imgui::GetKeyIndex(ImGuiKey_Delete))) {
				entity.remove<V::Component>();
			}

			Nova::imgui::EndPopup();
		}
	}

	template<size_t I = 0, typename V, typename... Vs, typename... Cs>
	void render_single(Nova::ecs::Entity& entity, std::tuple<Cs...>& tuple) {
		auto& component = std::get<I>(tuple);
		if (component) {
			Nova::imgui::PushID(V::title);
			bool copen = Nova::imgui::TreeNodeEx(V::title, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_AllowItemOverlap);
			context_menu<V>(entity);
			if (copen) {
				V::render(*component);
				//Nova::gui::TreePop(); // Not needed for Collapsing Header
				Nova::imgui::Separator();
			}
			Nova::imgui::PopID();
		}

		if constexpr (I + 1 != sizeof...(Cs))
			render_single<I + 1, Vs...>(entity, tuple);
	}

	template<size_t I = 0, typename V, typename... Vs, typename... Cs>
	void render_create(Nova::ecs::Entity& entity, std::tuple<Cs...>& tuple) {
		auto& component = std::get<I>(tuple);
		if (!component && Nova::imgui::Selectable(V::title)) {
			entity.emplace<V::Component>();
		}

		if constexpr (I + 1 != sizeof...(Cs))
			render_create<I + 1, Vs...>(entity, tuple);
	}

	template<typename... Views>
	void gui_impl(Nova::ecs::Entity& entity, const Nova::var::pack<Views...>&) {
		// Current Components
		auto components = entity.try_get<Views::Component...>();
		Nova::imgui::Text("ID: %d", (unsigned int)entity);
		render_single<0, Views...>(entity, components);

		// Create Components
		Nova::imgui::Spacing();
		if (Nova::imgui::BeginCombo("##cc", "Create Component", ImGuiComboFlags_NoArrowButton)) {
			render_create<0, Views...>(entity, components);
			Nova::imgui::EndCombo();
		}
	}



	void EntityComponents::gui() {
		auto& entity = hierarchy.entity();
		if (entity) {
			gui_impl(entity, PACK);
		} else {
			Nova::imgui::Text("No Entity Selected");
		}
	}

}