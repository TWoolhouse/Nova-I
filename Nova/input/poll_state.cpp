#include "npch.h"
#include "poll.h"

namespace Nova::Input {

	std::bitset<static_cast<size_t>(Key::_KEY_SIZE)> State::m_keys{};
	std::bitset<static_cast<size_t>(Mouse::_MOUSE_SIZE)> State::m_mouse{};

}