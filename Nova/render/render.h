#pragma once
#include "npch.h"
#include "buffer/context.h"
#include "shader.h"
#include "phys/maths.h"

namespace Nova {

	class NOVA_API Render {
	public:
		class NOVA_API Command;

		static bool Initialise();
		static bool Termintate();

		static void FrameSize(unsigned int width, unsigned int height);

		static void Scene(bool b); // Vars for starting
		static void Scene(); // Empty for end

		static void Flush();

		class NOVA_API Draw {
		public:
			static void Quad(const mlb::vec2& pos);
		};

	};

}