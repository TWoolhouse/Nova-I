#pragma once
#include "npch.h"

namespace Nova {

	class NOVA_API DeltaTime {
	public:
		operator double() const { return dt(); }
		static const double dt();
		constexpr static const double phys();

		static void update();
	};

}