#include "npch.h"
#include "random.h"
#include "lib.h"

namespace Nova::glm {

	std::mt19937 Random::m_gen = std::mt19937(std::random_device()());

}

std::ostream& operator<<(std::ostream& out, const Nova::glm::vec2& vec) {
	return out << vec.x << ", " << vec.y;
}
std::ostream& operator<<(std::ostream& out, const Nova::glm::vec3& vec) {
	return out << vec.x << ", " << vec.y << ", " << vec.z;
}
std::ostream& operator<<(std::ostream& out, const Nova::glm::vec4& vec) {
	return out << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
}
