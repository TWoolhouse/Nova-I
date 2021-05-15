#pragma once
#include "npch.h"

namespace Nova {

	class NOVA_API Render {
	public:
		class NOVA_API Command;
		class NOVA_API Camera;

		static bool Initialise();
		static bool Termintate();

		static void FrameSize(unsigned int width, unsigned int height);

		static void Draw(Camera* camera); // Vars for starting
		static void Draw(); // Empty for end

		// Draw Frame
		static void Frame();

		static void Flush();
	};

}