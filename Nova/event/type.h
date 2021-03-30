#pragma once

namespace Nova::Event {
	enum class Type : unsigned char {
		None = 0,
		Window, WindowClose, WindowFocus, WindowFocusLost, WindowFocusGain, WindowMove, WindowResize,
		Key, KeyPress, KeyRelease,
		Mouse, MouseButton, MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll,
	};
}