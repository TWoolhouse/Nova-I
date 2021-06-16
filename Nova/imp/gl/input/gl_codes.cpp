#include "npch.h"
#include "input/key.h"
#include "input/mouse.h"

namespace Nova::Input {

	const Key Nova::Input::WindowKeyCode(int code) {
		switch (code) {
		case 340:	return Key::LSHIFT;
		case 341:	return Key::LCTRL;
		case 342:	return Key::LALT;
		case 343:	return Key::LSUPER;
		case 344:	return Key::RSHIFT;
		case 345:	return Key::RCTRL;
		case 346:	return Key::ALTGR;
		case 347:	return Key::RSUPER;
		case 256:	return Key::ESCAPE;
		case 257:	return Key::ENTER;
		case 258:	return Key::TAB;
		case 259:	return Key::BACKSPACE;
		case 32:	return Key::SPACE;
		case 39:	return Key::APOSTROPHE;
		case 44:	return Key::COMMA;
		case 45:	return Key::MINUS;
		case 46:	return Key::PERIOD;
		case 47:	return Key::SLASH;
		case 59:	return Key::SEMICOLON;
		case 61:	return Key::EQUAL;
		case 91:	return Key::LBRACKET;
		case 92:	return Key::BACKSLASH;
		case 93:	return Key::RBRACKET;
		case 96:	return Key::GRAVE_ACCENT;
		case 48:	return Key::N0;
		case 49:	return Key::N1;
		case 50:	return Key::N2;
		case 51:	return Key::N3;
		case 52:	return Key::N4;
		case 53:	return Key::N5;
		case 54:	return Key::N6;
		case 55:	return Key::N7;
		case 56:	return Key::N8;
		case 57:	return Key::N9;
		case 65:	return Key::A;
		case 66:	return Key::B;
		case 67:	return Key::C;
		case 68:	return Key::D;
		case 69:	return Key::E;
		case 70:	return Key::F;
		case 71:	return Key::G;
		case 72:	return Key::H;
		case 73:	return Key::I;
		case 74:	return Key::J;
		case 75:	return Key::K;
		case 76:	return Key::L;
		case 77:	return Key::M;
		case 78:	return Key::N;
		case 79:	return Key::O;
		case 80:	return Key::P;
		case 81:	return Key::Q;
		case 82:	return Key::R;
		case 83:	return Key::S;
		case 84:	return Key::T;
		case 85:	return Key::U;
		case 86:	return Key::V;
		case 87:	return Key::W;
		case 88:	return Key::X;
		case 89:	return Key::Y;
		case 90:	return Key::Z;
		case 260:	return Key::INSERT;
		case 261:	return Key::DELETE;
		case 262:	return Key::RIGHT;
		case 263:	return Key::LEFT;
		case 264:	return Key::DOWN;
		case 265:	return Key::UP;
		case 266:	return Key::PGUP;
		case 267:	return Key::PGDN;
		case 268:	return Key::HOME;
		case 269:	return Key::END;
		case 280:	return Key::CAPS_LOCK;
		case 281:	return Key::SCROLL_LOCK;
		case 282:	return Key::NUM_LOCK;
		case 283:	return Key::PRINT_SCREEN;
		case 284:	return Key::PAUSE;
		case 320:	return Key::KP_0;
		case 321:	return Key::KP_1;
		case 322:	return Key::KP_2;
		case 323:	return Key::KP_3;
		case 324:	return Key::KP_4;
		case 325:	return Key::KP_5;
		case 326:	return Key::KP_6;
		case 327:	return Key::KP_7;
		case 328:	return Key::KP_8;
		case 329:	return Key::KP_9;
		case 330:	return Key::KP_DELETE;
		case 331:	return Key::KP_DIVIDE;
		case 332:	return Key::KP_MULTIPLY;
		case 333:	return Key::KP_SUBTRACT;
		case 334:	return Key::KP_ADD;
		case 335:	return Key::KP_ENTER;
		case 290:	return Key::F1;
		case 292:	return Key::F2;
		case 293:	return Key::F3;
		case 294:	return Key::F4;
		case 295:	return Key::F5;
		case 296:	return Key::F6;
		case 297:	return Key::F7;
		case 298:	return Key::F8;
		case 299:	return Key::F9;
		case 300:	return Key::F10;
		case 301:	return Key::F11;
		case 302:	return Key::F12;
		case 303:	return Key::F13;
		case 304:	return Key::F14;
		case 305:	return Key::F15;
		case 306:	return Key::F16;
		case 307:	return Key::F17;
		case 308:	return Key::F18;
		case 309:	return Key::F19;
		case 310:	return Key::F20;
		case 311:	return Key::F21;
		case 312:	return Key::F22;
		case 313:	return Key::F23;
		case 314:	return Key::F24;
		case 348:	return Key::LMENU;

		default:
			return Key::None;
		}
	}

	const Mouse Nova::Input::WindowMouseCode(int code) {
		switch (code) {
		case 0:	return Mouse::LMB;
		case 1:	return Mouse::RMB;
		case 2:	return Mouse::MMB;
		case 3:	return Mouse::VB1;
		case 4:	return Mouse::VB2;

		default:
			return Mouse::None;
		}
	}

	const int Nova::Input::WindowCode(const Key& key) {
		switch (key) {
		case Key::LSHIFT:	return 340;
		case Key::LCTRL:	return 341;
		case Key::LALT:	return 342;
		case Key::LSUPER:	return 343;
		case Key::RSHIFT:	return 344;
		case Key::RCTRL:	return 345;
		case Key::ALTGR:	return 346;
		case Key::RSUPER:	return 347;
		case Key::ESCAPE:	return 256;
		case Key::ENTER:	return 257;
		case Key::TAB:	return 258;
		case Key::BACKSPACE:	return 259;
		case Key::SPACE:	return 32;
		case Key::APOSTROPHE:	return 39;
		case Key::COMMA:	return 44;
		case Key::MINUS:	return 45;
		case Key::PERIOD:	return 46;
		case Key::SLASH:	return 47;
		case Key::SEMICOLON:	return 59;
		case Key::EQUAL:	return 61;
		case Key::LBRACKET:	return 91;
		case Key::BACKSLASH:	return 92;
		case Key::RBRACKET:	return 93;
		case Key::GRAVE_ACCENT:	return 96;
		case Key::N0:	return 48;
		case Key::N1:	return 49;
		case Key::N2:	return 50;
		case Key::N3:	return 51;
		case Key::N4:	return 52;
		case Key::N5:	return 53;
		case Key::N6:	return 54;
		case Key::N7:	return 55;
		case Key::N8:	return 56;
		case Key::N9:	return 57;
		case Key::A:	return 65;
		case Key::B:	return 66;
		case Key::C:	return 67;
		case Key::D:	return 68;
		case Key::E:	return 69;
		case Key::F:	return 70;
		case Key::G:	return 71;
		case Key::H:	return 72;
		case Key::I:	return 73;
		case Key::J:	return 74;
		case Key::K:	return 75;
		case Key::L:	return 76;
		case Key::M:	return 77;
		case Key::N:	return 78;
		case Key::O:	return 79;
		case Key::P:	return 80;
		case Key::Q:	return 81;
		case Key::R:	return 82;
		case Key::S:	return 83;
		case Key::T:	return 84;
		case Key::U:	return 85;
		case Key::V:	return 86;
		case Key::W:	return 87;
		case Key::X:	return 88;
		case Key::Y:	return 89;
		case Key::Z:	return 90;
		case Key::INSERT:	return 260;
		case Key::DELETE:	return 261;
		case Key::RIGHT:	return 262;
		case Key::LEFT:	return 263;
		case Key::DOWN:	return 264;
		case Key::UP:	return 265;
		case Key::PGUP:	return 266;
		case Key::PGDN:	return 267;
		case Key::HOME:	return 268;
		case Key::END:	return 269;
		case Key::CAPS_LOCK:	return 280;
		case Key::SCROLL_LOCK:	return 281;
		case Key::NUM_LOCK:	return 282;
		case Key::PRINT_SCREEN:	return 283;
		case Key::PAUSE:	return 284;
		case Key::KP_0:	return 320;
		case Key::KP_1:	return 321;
		case Key::KP_2:	return 322;
		case Key::KP_3:	return 323;
		case Key::KP_4:	return 324;
		case Key::KP_5:	return 325;
		case Key::KP_6:	return 326;
		case Key::KP_7:	return 327;
		case Key::KP_8:	return 328;
		case Key::KP_9:	return 329;
		case Key::KP_DELETE:	return 330;
		case Key::KP_DIVIDE:	return 331;
		case Key::KP_MULTIPLY:	return 332;
		case Key::KP_SUBTRACT:	return 333;
		case Key::KP_ADD:	return 334;
		case Key::KP_ENTER:	return 335;
		case Key::F1:	return 290;
		case Key::F2:	return 292;
		case Key::F3:	return 293;
		case Key::F4:	return 294;
		case Key::F5:	return 295;
		case Key::F6:	return 296;
		case Key::F7:	return 297;
		case Key::F8:	return 298;
		case Key::F9:	return 299;
		case Key::F10:	return 300;
		case Key::F11:	return 301;
		case Key::F12:	return 302;
		case Key::F13:	return 303;
		case Key::F14:	return 304;
		case Key::F15:	return 305;
		case Key::F16:	return 306;
		case Key::F17:	return 307;
		case Key::F18:	return 308;
		case Key::F19:	return 309;
		case Key::F20:	return 310;
		case Key::F21:	return 311;
		case Key::F22:	return 312;
		case Key::F23:	return 313;
		case Key::F24:	return 314;
		case Key::LMENU:	return 348;

		default:
			return -1;
		}
	}

	const int Nova::Input::WindowCode(const Mouse& button) {
		switch (button) {
		case Mouse::LMB:	return 0;
		case Mouse::RMB:	return 1;
		case Mouse::MMB:	return 2;
		case Mouse::VB1:	return 3;
		case Mouse::VB2:	return 4;

		default:
			return -1;
		}
	}

}
