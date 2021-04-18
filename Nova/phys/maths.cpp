#include "npch.h"
#include "random.h"

namespace Nova::mlb {

	std::mt19937 Random::m_gen = std::mt19937(std::random_device()());

}