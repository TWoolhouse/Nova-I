#pragma once
#include "npch.h"

#define IMGUI_API NOVA_API
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include "event/event.h"
#include "phys/lib.h"

namespace Nova::imgui {
	using namespace ::ImGui;

	class NOVA_API App {
	public:
		static Star<App> Create();
		App();
		virtual ~App() {}

		virtual void begin() = 0;
		virtual void end() = 0;
		void event(Nova::Event::Event& event);
		void block_events(bool block) { m_block = block; }
		const bool blocking() const { return m_block; }

		bool& render_viewport(bool& open);
	protected:
		bool m_block = false;
		void setup();
	};

}