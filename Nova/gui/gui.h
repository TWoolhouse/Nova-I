#pragma once
#include "npch.h"
#include "event/event.h"

#define IMGUI_API NOVA_API
#ifndef NOVA_EXPORT
#include "dep/imgui/imgui/imgui.h"
#else
#include <imgui/imgui.h>
#endif // NOVA_EXPORT

#include "phys/lib.h"

namespace Nova::gui {

	inline ImVec2 vec(const mlb::vec2& v) {
		return { v.x, v.y };
	}
	inline ImVec4 vec(const mlb::vec4& v) {
		return { v.x, v.y, v.z, v.w };
	}

	using namespace ImGui;

	class NOVA_API App {
	public:
		static Star<App> Create();
		App();
		virtual ~App() {}

		virtual void begin() = 0;
		virtual void end() = 0;
		void event(Nova::Event::Event& event);
		void block_events(bool block) { m_block = block; }
	protected:
		bool m_block = false;
		void setup();
	};

}