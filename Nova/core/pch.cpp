#include "npch.h"

void NOVA_API _nova_assert(const bool& flag, const std::string& msg, const char* file, const long line) {
	if (!flag) {
		std::cerr << "File: " << file << " @ Line: " << line << "\nAssertion: " << msg << std::endl;
		std::abort();
	}
}