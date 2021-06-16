#pragma once
#include "npch.h"
#include "key.h"
#include "mouse.h"

namespace Nova::Input {

	struct NOVA_API State {
	public:
		static bool get(const Key& key) { return m_keys[static_cast<unsigned char>(key)]; }
		static bool get(const Mouse& mouse) { return m_mouse[static_cast<unsigned char>(mouse)]; }

		static void set(const Key& key, const bool& flag) { m_keys[static_cast<unsigned char>(key)] = flag; }
		static void set(const Mouse& mouse, const bool& flag) { m_mouse[static_cast<unsigned char>(mouse)] = flag; }
	protected:
		static std::bitset<static_cast<size_t>(Key::_KEY_SIZE)> m_keys;
		static std::bitset<static_cast<size_t>(Mouse::_MOUSE_SIZE)> m_mouse;
	};

	inline const bool Poll(const Key& key) { return State::get(key); }
	inline const std::pair<int, int> NOVA_API Poll();
	inline const bool Poll(const Mouse& button) { return State::get(button); }

	const bool NOVA_API PollWin(const Key& key);
	const bool NOVA_API PollWin(const Mouse& button);

}