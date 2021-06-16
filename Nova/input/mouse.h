#pragma once

namespace Nova::Input {

	enum class Mouse : unsigned char {
		None = 0,
		LMB = 1, RMB, MMB, VB1, VB2,

		_MOUSE_SIZE
	};

	const Mouse WindowMouseCode(int code);
	const int WindowCode(const Mouse& button);

}