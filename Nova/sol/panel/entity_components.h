#pragma once
#include "npch.h"
#include "base.h"
#include "ecs/entity.h"
#include "entity_hierarchy.h"
#include "../view/base.h"

#include "../view/views.h"
// Needed for Name & Transform

namespace Nova::sol::Panel {

	template<View::Viewable ...Views >
	class EntityComponents : public Base {
	public:
		EntityComponents(EntityHierarchy& hierarchy, const Nova::var::pack<Views...>&) : Base("Entity Components"), m_entity(hierarchy.entity()) {}
	protected:
		Nova::ecs::Entity& m_entity;

	private:
		template<View::Viewable V>
		void context_menu() {
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
						m_entity.remove<V::Component>();
					}

				Nova::imgui::EndPopup();
			}
		}

		template<size_t I = 0, View::Viewable V, View::Viewable... Vs, typename... Cs>
		void render_single(std::tuple<Cs...>& tuple) {
			auto& component = std::get<I>(tuple);
			if (component) {
				Nova::imgui::PushID(V::title);
				bool copen = Nova::imgui::TreeNodeEx(V::title, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_AllowItemOverlap);
				context_menu<V>();
				if (copen) {
					V::render(*component);
					//Nova::gui::TreePop(); // Not needed for Collapsing Header
					Nova::imgui::Separator();
				}
				Nova::imgui::PopID();
			}

			if constexpr (I + 1 != sizeof...(Cs))
				render_single<I + 1, Vs...>(tuple);
		}

		template<size_t I = 0, View::Viewable V, View::Viewable... Vs, typename... Cs>
		void render_create(std::tuple<Cs...>& tuple) {
			auto& component = std::get<I>(tuple);
			if (!component && Nova::imgui::Selectable(V::title)) {
				m_entity.emplace<V::Component>();
			}

			if constexpr (I + 1 != sizeof...(Cs))
				render_create<I + 1, Vs...>(tuple);
		}

	protected:
		void gui() override {
			// Current Components
			auto components = m_entity.try_get<Views::Component...>();
			Nova::imgui::Text("ID: %d", (unsigned int)m_entity);
			render_single<0, Views...>(components);

			// Create Components
			Nova::imgui::Spacing();
			if (Nova::imgui::BeginCombo("##cc", "Create Component", ImGuiComboFlags_NoArrowButton)) {
				render_create<0, Views...>(components);
				Nova::imgui::EndCombo();
			}
		}
	};

}