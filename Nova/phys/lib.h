#pragma once

#ifndef NDEBUG
	#define GLM_FORCE_PURE
#else
	#define GLM_FORCE_INTRINSICS
	#define GLM_FORCE_INLINE
#endif // NDEBUG
#define GLM_ENABLE_EXPERIMENTAL

#ifndef NOVA_EXPORT
#include "dep/glm/include/glm/fwd.hpp"
#include "dep/glm/include/glm/glm.hpp"
#include "dep/glm/include/glm/ext.hpp"
#else
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#endif // NOVA_EXPORT

namespace Nova::mlb {
	using namespace glm;
}
