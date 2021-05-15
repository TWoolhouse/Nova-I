#pragma once
#include "npch.h"
#include "event/event.h"

namespace Nova {

	class Layer {
	public:
		Layer() {}
		virtual ~Layer() {}

		virtual void update() = 0;
		virtual void event(Event::Event& event) = 0;
	};

}
