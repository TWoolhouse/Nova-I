#pragma once
#include "npch.h"
#include "gui/gui.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imconfig.h>

namespace Nova::OpenGL {

	class GuiApp : public imgui::App {
	public:
		GuiApp();
		virtual ~GuiApp();

		virtual void begin() override;
		virtual void end() override;

	protected:
		ImGuiContext* m_context;
	};

}