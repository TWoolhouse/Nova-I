#pragma once
#include "spch.h"
#include <nova.h>
#include "core/panel.h"
#include <filesystem>

namespace Sol::Panel {
	class AssetExplorer : public Panel {
	public:
		AssetExplorer();
	protected:
		virtual void gui() override;
		
	};
}
