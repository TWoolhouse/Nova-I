#pragma once
#include "npch.h"
#include "gui/gui.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imconfig.h>

namespace Nova::OpenGL {

	class GuiApp : public gui::App {
	public:
		GuiApp();
		virtual ~GuiApp();

		virtual void begin() override;
		virtual void end() override;

	protected:
		ImGuiContext* m_context;
	};

}