#pragma once
#include "npch.h"
#include "event/event.h"

namespace Nova::Layer {

	class Item {
	public:
		Item() {}
		virtual ~Item() {}

		virtual void update() = 0;
		virtual void event(Event::Event& event) = 0;
	};

	class Stack {
	public:
		Stack() {}

		void update() {
			for (auto& it : m_stack) {
				it->update();
			}
		}
		void event(Event::Event& event) {
			for (auto it = m_stack.rbegin(); it < m_stack.crend(); ++it) {
				if (event.done)
					break;
				(*it)->event(event);
			}
		}
	protected:
		std::vector<Item*> m_stack;
	};

}
