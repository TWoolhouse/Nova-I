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
				Nova::gui::Text("VSync");
				Nova::gui::SameLine();
				Nova::gui::Checkbox("##vsync", &vsync);
				if (vsync != Nova::Render::Command::VSync())
					Nova::Render::Command::VSync(vsync);
			}
			
		}
	};
}