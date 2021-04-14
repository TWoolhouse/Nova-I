#pragma once

#ifdef NOVA
#include "dep/glm/include/glm/fwd.hpp"
#include "dep/glm/include/glm/glm.hpp"
#include "dep/glm/include/glm/ext.hpp"
#else
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#endif NOVA

namespace Nova::mlb {
	using namespace glm;
}
