#pragma once
#include "npch.h"

#ifndef NOVA_RELEASE
	#define GLM_FORCE_PURE
#else
	#define GLM_FORCE_INTRINSICS
	#define GLM_FORCE_INLINE
#endif // NOVA_RELEASE
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

NOVA_API std::ostream& operator<<(std::ostream& out, const Nova::mlb::vec2& vec);
NOVA_API std::ostream& operator<<(std::ostream& out, const Nova::mlb::vec3& vec);
NOVA_API std::ostream& operator<<(std::ostream& out, const Nova::mlb::vec4& vec);
