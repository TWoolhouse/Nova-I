#pragma once
#include "npch.h"
#include "render/draw.h"

namespace Nova::RenderDraw {

	class Draw {
	public:
		static void Initialise() { assert(false, "Abstract Class"); }
		static void Terminate() { assert(false, "Abstract Class"); }
		static void Flush() { assert(false, "Abstract Class"); }
	};

}