#pragma once
#include "spch.h"
#include <nova.h>
#include "core/panel.h"

namespace Sol::Panel {
	class SceneHierarchy : public Panel {
	public:
		SceneHierarchy() : Panel("Scene Hierarchy") {}
		Nova::ecs::Entity& entity() { return m_selected; }
	protected:
		virtual void gui() override;

		Nova::Star<Nova::ecs::World> world;
		Nova::ecs::Entity m_selected;
		bool m_selected_valid = false;

		struct HierarchyTree {
			template<typename T>
			struct Node {
				Node(const T& data) : data(data), children() {}
				T data;
				std::vector<Node<T>*> children;
				std::vector<Node<T>*>& traverse() {
					std::sort(children.begin(), children.end(), [](Node<T>*& a, Node<T>*& b) -> bool {
						return std::get<1>(a->data) < std::get<1>(b->data);
					});
					return children;
				}
			};
			using E = std::tuple<Nova::ecs::Entity::Type, std::string, Nova::Component::Parent*>;
			using Trees = std::unordered_map<Nova::ecs::Entity::Type, Node<E>*>;
			void insert(Nova::ecs::Entity entity, Nova::Component::Name* name, Nova::Component::Parent* parent);
			void insert(Nova::ecs::Entity entity, Nova::Component::Name* name);

			HierarchyTree() = default;
			HierarchyTree(const size_t& count) : trees(count) {};
			~HierarchyTree() {
				for (auto&& [k, v] : trees) {
					delete v;
				}
			}

			std::vector<Node<E>*>& traverse() {
				std::sort(roots.begin(), roots.end(), [](Node<E>*& a, Node<E>*& b) -> bool {
					return std::get<1>(a->data) < std::get<1>(b->data);
				});
				return roots;
			}

		protected:
			Trees trees;
			std::vector<Node<E>*> roots;
		};
		void traverse(Nova::Star<Nova::ecs::World>& world, Nova::ecs::Registry& reg, HierarchyTree::Node<HierarchyTree::E>& node);
		void delete_entity_recurse(Nova::ecs::Entity& entity, HierarchyTree::Node<HierarchyTree::E>& node);
		void create_entity(const Nova::ecs::Entity* parent=nullptr);
	};
}