#pragma once
#include "spch.h"
#include <nova.h>
#include "core/panel.h"

namespace Sol::Panel {
	class Stats : public Panel {
	public:
		Stats() : Panel("Stats") {}
		void state(const std::string& state) { m_state = state; }
	protected:
		std::string m_state = "Nominal";
		virtual void gui() override {
			Nova::imgui::Text("CPU Time: %f", Nova::DeltaTime::dt() * 1000.0f);
			Nova::imgui::Text("State: %s", m_state.c_str());
			m_state = "Nominal";
		}
	};
}