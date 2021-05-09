#pragma once
#include "npch.h"

namespace Nova {

	class NOVA_API DeltaTime {
	public:
		operator double() const { return dt(); }
		static const float dt();
		constexpr static const float phys();

		static inline void update();
	};

}