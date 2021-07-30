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

		world = static_cast<App*>(&Nova::App())->world;
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
		Nova::imgui::Dummy(Nova::imgui::GetContentRegionAvail());
		if (Nova::imgui::BeginDragDropTarget()) {
			if (auto payload = Nova::imgui::AcceptDragDropPayload(payload_type)) {
				Nova::ecs::Entity nchild{ reg , *static_cast<Nova::ecs::Entity::Type*>(payload->Data) };
				nchild.remove<Nova::Component::Parent>();
			}
			Nova::imgui::EndDragDropTarget();
		}
		if (Nova::imgui::BeginPopupContextWindow(context_menu, ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight)) {
			if (Nova::imgui::MenuItem("Create New Entity")) {
				create_entity();
			}
			Nova::imgui::EndPopup();
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
		Nova::imgui::PushID(std::to_string(entity).c_str());
		const auto topen = Nova::imgui::TreeNodeExV(std::to_string(entity).c_str(), flags, name.c_str(), "");
		if (Nova::imgui::BeginDragDropSource()) {
			auto eid = entity.entity();
			Nova::imgui::SetDragDropPayload(payload_type, static_cast<void*>(&eid), sizeof(decltype(eid)));
			Nova::imgui::Text(name.c_str());
			Nova::imgui::EndDragDropSource();
		}
		auto payload = Nova::imgui::GetDragDropPayload();
		if (payload && payload->IsDataType(payload_type)) {
			auto& payload_entt = *static_cast<Nova::ecs::Entity::Type*>(payload->Data);
			auto pentt = entity.try_get<Nova::Component::Parent>();
			bool flag = true;
			while (pentt) {
				if (pentt->entity == payload_entt) {
					flag = false;
					break;
				}
				pentt = Nova::ecs::Entity{ reg, pentt->entity }.try_get<Nova::Component::Parent>();
			}

			if (flag && Nova::imgui::BeginDragDropTarget()) {
				if (payload = Nova::imgui::AcceptDragDropPayload(payload_type)) {
					Nova::ecs::Entity nchild{ reg , *static_cast<Nova::ecs::Entity::Type*>(payload->Data) };
					auto& nparent = nchild.get_or_emplace<Nova::Component::Parent>(entity);
					nparent.entity = entity;
				}
				Nova::imgui::EndDragDropTarget();
			}
		}
		if ((Nova::imgui::IsMouseClicked(ImGuiMouseButton_Left) || Nova::imgui::IsKeyPressed(Nova::imgui::GetKeyIndex(ImGuiKey_Enter))) && Nova::imgui::IsItemHovered()) {
			m_selected = entity;
			m_selected_valid = true;
		}
		if (Nova::imgui::BeginPopupContextItem(context_menu)) {
			if (Nova::imgui::MenuItem("Create Child Entity")) {
				create_entity(&entity);
			}
			if (Nova::imgui::MenuItem("Delete Entity")) {
				delete_entity_recurse(entity, node);
			}
			Nova::imgui::EndPopup();
		}
		if (Nova::imgui::IsItemHovered()) {
			constexpr auto button_str = "...";
			Nova::imgui::SameLine(Nova::imgui::GetContentRegionMax().x - Nova::imgui::CalcTextSize(button_str).x - 2 * Nova::imgui::GetStyle().FramePadding.x);
			if (Nova::imgui::SmallButton(button_str) || Nova::imgui::IsItemClicked()) {
				Nova::imgui::OpenPopup(context_menu);
			}
		}
		if (topen) {
			if (!node.children.empty() && entity)
				for (auto& child : node.traverse())
					traverse(world, reg, *child);
			Nova::imgui::TreePop();
		}

		Nova::imgui::PopID();
	}

	void SceneHierarchy::create_entity(const Nova::ecs::Entity* parent) {
		auto e = world->instantiate();
		e.emplace<Nova::Component::Name>("New Entity");
		e.emplace<Nova::Component::Transform>();
		if (parent) {
			const auto& p = *parent;
			e.emplace<Nova::Component::Parent>(p);
		}
		m_selected = e;
		m_selected_valid = true;
	}

}