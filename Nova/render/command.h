#pragma once
#include "npch.h"
#include "render.h"
#include "buffer/context.h"

namespace Nova {

	class NOVA_API Render::Command {
	public:
		static bool Initialise();
		static bool Termintate();

		static void SwapBuffers();
		static void Viewport(unsigned int width, unsigned int height);
		static void Viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

		static void Clear();
		static void ClearColour(float r= 0.0, float g= 0.0, float b=0.0, float a=1.0);

		static void Depth(bool enable);

		static void Draw(Buffer::Context* bc) { Draw(bc, bc->index().count()); }
		static void Draw(Buffer::Context* bc, const unsigned int count);
		static void DrawPoint(Buffer::Context* bc) { DrawPoint(bc, bc->index().count()); }
		static void DrawPoint(Buffer::Context* bc, const unsigned int count);

		// Move out to properties?
		static void VSync(const bool flag);

	};

}