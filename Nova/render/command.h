#pragma once
#include "npch.h"
#include "render.h"
#include "buffer/array.h"

namespace Nova {

	class NOVA_API Render::Command {
	public:
		static bool Initialise();
		static bool Termintate();

		static void SwapBuffers();
		static void Viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		static void Clear();
		static void ClearColour(float r= 0.0, float g= 0.0, float b=0.0, float a=1.0);

		static void Draw(Buffer::Context* bc);

		// Move out to properties?
		static void VSync(const bool flag);

	};

}