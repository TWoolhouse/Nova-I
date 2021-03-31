#pragma once
#include "npch.h"
#include "key.h"
#include "mouse.h"

namespace Nova::Input {

	inline const bool NOVA_API Poll(const Key& key);
	inline const std::pair<int, int> NOVA_API Poll();
	inline const bool NOVA_API Poll(const Mouse& button);

}