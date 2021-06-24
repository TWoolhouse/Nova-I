#pragma once
#include "spch.h"
#include <nova.h>
#include "component_views/view.h"

#include "component_views/basic.h"

namespace Sol::View {

	using Views = Nova::var::pack<
		Name,
		Transform,
		Sprite
	>;

}