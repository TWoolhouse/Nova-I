#include "npch.h"
#include "random.h"
#include "lib.h"

namespace Nova::mlb {

	std::mt19937 Random::m_gen = std::mt19937(std::random_device()());

}

std::ostream& operator<<(std::ostream& out, const Nova::mlb::vec2& vec) {
	return out << vec.x << ", " << vec.y;
}
std::ostream& operator<<(std::ostream& out, const Nova::mlb::vec3& vec) {
	return out << vec.x << ", " << vec.y << ", " << vec.z;
}
std::ostream& operator<<(std::ostream& out, const Nova::mlb::vec4& vec) {
	return out << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
}
