#include "spch.h"
#include <nova.h>
#include "scene_hierarchy.h"

#include "core/app.h"

namespace Sol::Panel {

	constexpr static auto context_menu = "EntCntxtMenu";
	constexpr static auto payload_type = "SceneHierarchy Entity";

	void SceneHierarchy::HierarchyTree::insert(Nova::ecs::Entity entity, Nova::Component::Name* name, Nova::Component::Parent* parent) {
		E e{ entity, name->name, parent };
		Node<E>* node = nullptr;

		Trees::iterator s = trees.find(entity);;
		while (s == trees.cend() && parent) {
			auto n = new Node<E>({ entity, name->name, parent });
			if (node)
				n->children.push_back(node);
			node = n;
			trees[std::get<0>(node->data)] = node;
			entity = { entity.registry(), parent->entity };
			name = &entity.get<Nova::Component::Name>();
			parent = entity.try_get<Nova::Component::Parent>();
			s = trees.find(entity);
		}
		if (node) {
			s->second->children.push_back(node);
		}
	}
	void SceneHierarchy::HierarchyTree::insert(Nova::ecs::Entity entity, Nova::Component::Name* name) {
		trees[entity] = roots.emplace_back(new Node<E>({ entity, name->name, nullptr }));
	}

	void SceneHierarchy::gui() {

		auto& app = *static_cast<App*>(&Nova::App());
		auto& world = app.world;
		auto& reg = world->registry;

		auto v = reg.view<Nova::Component::Name>(Nova::entt::exclude<Nova::Component::Parent>);

		HierarchyTree tree{ v.size_hint() };

		for (auto&& [e, name] : v.each()) {
			tree.insert({ reg, e }, &name);
		}
		for (auto&& [e, name, parent] : reg.view<Nova::Component::Name, Nova::Component::Parent>().each()) {
			tree.insert({ reg, e }, &name, &parent);
		}

		m_selected_valid = false;
		for (auto& root : tree.traverse()) {
			traverse(world, reg, *root);
		}
		Nova::gui::Dummy(Nova::gui::GetContentRegionAvail());
		if (Nova::gui::BeginDragDropTarget()) {
			if (auto payload = Nova::gui::AcceptDragDropPayload(payload_type)) {
				Nova::ecs::Entity nchild{ reg , *static_cast<Nova::ecs::Entity::Type*>(payload->Data) };
				nchild.remove_if_exists<Nova::Component::Parent>();
			}
			Nova::gui::EndDragDropTarget();
		}
		//static constexpr auto context_menu = ;
		if (Nova::gui::BeginPopupContextWindow(context_menu, ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight)) {
			if (Nova::gui::MenuItem("Create New Entity")) {
				auto e = world->instantiate();
				e.emplace<Nova::Component::Name>("New Entity");
				e.emplace<Nova::Component::Transform>();
			}
			Nova::gui::EndPopup();
		}

		if (!m_selected_valid)
			m_selected = {};
	}

	void SceneHierarchy::delete_entity_recurse(Nova::ecs::Entity& entity, HierarchyTree::Node<HierarchyTree::E>& node) {
		if (m_selected == entity) {
			m_selected = {};
			m_selected_valid = false;
		}
		for (auto& child : node.children) {
			delete_entity_recurse(Nova::ecs::Entity{ entity.registry(), std::get<0>(child->data) }, *child);
		}

		entity.remove_all();
		entity.destroy();
	}

	void SceneHierarchy::traverse(Nova::Star<Nova::ecs::World>& world, Nova::ecs::Registry& reg, HierarchyTree::Node<HierarchyTree::E>& node) {
		constexpr static ImGuiTreeNodeFlags s_flags = ImGuiTreeNodeFlags_NavLeftJumpsBackHere
			| ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen
			| ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth;
		Nova::ecs::Entity entity{ reg, std::get<0>(node.data) };
		if (entity == m_selected)
			m_selected_valid = true;
		auto flags = s_flags;
		if (node.children.empty())
			flags |= ImGuiTreeNodeFlags_Leaf;
		if (entity == m_selected)
			flags |= ImGuiTreeNodeFlags_Selected;

		auto& name = std::get<1>(node.data);
		Nova::gui::PushID(std::to_string(entity).c_str());
		const auto topen = Nova::gui::TreeNodeExV(std::to_string(entity).c_str(), flags, name.c_str(), "");
		if (Nova::gui::BeginDragDropSource()) {
			auto eid = entity.entity();
			Nova::gui::SetDragDropPayload(payload_type, static_cast<void*>(&eid), sizeof(decltype(eid)));
			Nova::gui::Text(name.c_str());
			Nova::gui::EndDragDropSource();
		}
		auto payload = Nova::gui::GetDragDropPayload();
		if (payload && payload->IsDataType(payload_type)) {
			if (Nova::gui::BeginDragDropTarget()) {
				if (payload = Nova::gui::AcceptDragDropPayload(payload_type)) {
					Nova::ecs::Entity nchild{ reg , *static_cast<Nova::ecs::Entity::Type*>(payload->Data) };
					auto& nparent = nchild.get_or_emplace<Nova::Component::Parent>(entity);
					nparent.entity = entity;
				}
				Nova::gui::EndDragDropTarget();
			}
		}
		if ((Nova::gui::IsMouseClicked(ImGuiMouseButton_Left) || Nova::gui::IsKeyPressed(Nova::gui::GetKeyIndex(ImGuiKey_Enter))) && Nova::gui::IsItemHovered()) {
			m_selected = entity;
			m_selected_valid = true;
		}
		if (Nova::gui::BeginPopupContextItem(context_menu)) {
			if (Nova::gui::MenuItem("Create Child Entity")) {
				auto e = world->instantiate();
				e.emplace<Nova::Component::Name>("New Entity");
				e.emplace<Nova::Component::Transform>();
				e.emplace<Nova::Component::Parent>(entity);
			}
			if (Nova::gui::MenuItem("Delete Entity")) {
				delete_entity_recurse(entity, node);
			}
			Nova::gui::EndPopup();
		}
		if (Nova::gui::IsItemHovered()) {
			constexpr auto button_str = "...";
			Nova::gui::SameLine(Nova::gui::GetContentRegionMax().x - Nova::gui::CalcTextSize(button_str).x - 2 * Nova::gui::GetStyle().FramePadding.x);
			if (Nova::gui::SmallButton(button_str) || Nova::gui::IsItemClicked()) {
				Nova::gui::OpenPopup(context_menu);
			}
		}
		if (topen) {
			if (!node.children.empty() && entity)
				for (auto& child : node.traverse())
					traverse(world, reg, *child);
			Nova::gui::TreePop();
		}

		Nova::gui::PopID();
	}

}