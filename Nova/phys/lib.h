#pragma once
#include "npch.h"

#ifndef NOVA_RELEASE
	#define GLM_FORCE_PURE
#else
	#define GLM_FORCE_INTRINSICS
	#define GLM_FORCE_INLINE
#endif // NOVA_RELEASE
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Nova::glm {
	using namespace ::glm;
}

#include "serial/cereal.h"

NovaCerealiseExtern(Nova::glm::vec2, vec) { serialise(vec.x, vec.y); }
NovaCerealiseExtern(Nova::glm::vec3, vec) { serialise(vec.x, vec.y, vec.z); }
NovaCerealiseExtern(Nova::glm::vec4, vec) { serialise(vec.x, vec.y, vec.z, vec.w); }

NOVA_API std::ostream& operator<<(std::ostream& out, const Nova::glm::vec2& vec);
NOVA_API std::ostream& operator<<(std::ostream& out, const Nova::glm::vec3& vec);
NOVA_API std::ostream& operator<<(std::ostream& out, const Nova::glm::vec4& vec);
