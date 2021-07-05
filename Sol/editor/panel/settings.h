#pragma once
#include "spch.h"
#include <nova.h>
#include "core/panel.h"

namespace Sol::Panel {
	class Settings : public Panel {
	public:
		Settings() : Panel("Settings") {}
	protected:
		virtual void gui() override {
			{
				bool vsync = Nova::Render::Command::VSync();
				Nova::imgui::Text("VSync");
				Nova::imgui::SameLine();
				Nova::imgui::Checkbox("##vsync", &vsync);
				if (vsync != Nova::Render::Command::VSync())
					Nova::Render::Command::VSync(vsync);
			}
			
		}
	};
}