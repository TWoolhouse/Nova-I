#include "npch.h"
#include <iostream>

void _nova_assert(const bool& flag, const std::string& msg) {
	if (!flag) {
		std::cerr << "File: " << __FILE__ << " @ Line: " << __LINE__ << "\nAssertion: " << msg << std::endl;
		std::abort();
	}
}