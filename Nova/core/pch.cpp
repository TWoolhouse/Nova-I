#include "npch.h"

void NOVA_API __n_ova_assert(const bool flag, const std::string& msg, cstring file, const long line) {
	if (!flag) {
		std::cerr << "File: " << file << " @ Line: " << line << "\nAssertion: " << msg << std::endl;
		std::abort();
	}
}