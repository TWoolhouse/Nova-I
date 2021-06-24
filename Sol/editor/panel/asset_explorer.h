#pragma once
#include "spch.h"
#include <nova.h>
#include "core/panel.h"

namespace Sol::Panel {
	class AssetExplorer : public Panel {
	public:
		AssetExplorer() : Panel("Asset Explorer", ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse) {}
	protected:
		virtual void gui() override;
	};
}
