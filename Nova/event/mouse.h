#pragma once
#include "event.h"
#include "input/mouse.h"

namespace Nova::Event {

	class Mouse : public Event {
	public:
		friend Event;
		Mouse() : Event() {}
	protected:
		Mouse(const bool cast) : Event(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::Mouse;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Mouse;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
	};

	class MouseButton : public Mouse {
	public:
		friend Event;
		MouseButton(const Input::Mouse& button) : Mouse(), m_button(button) {}
		const bool match(const Input::Mouse& button) const { return m_button == button; }
		const Input::Mouse& button() const { return m_button; }
	protected:
		MouseButton(const bool cast) : Mouse(cast), m_button(Input::Mouse::None) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::MouseButton;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Mouse;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
		const Input::Mouse m_button;
	};

	class MouseButtonPress : public MouseButton {
	public:
		friend Event;
		MouseButtonPress(const Input::Mouse& button) : MouseButton(button) {}
	protected:
		MouseButtonPress(const bool cast) : MouseButton(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::MouseButtonPress;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Mouse;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
	};

	class MouseButtonRelease : public MouseButton {
	public:
		friend Event;
		MouseButtonRelease(const Input::Mouse& button) : MouseButton(button) {}
	protected:
		MouseButtonRelease(const bool cast) : MouseButton(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::MouseButtonRelease;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Mouse;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
	};

	class MouseMove : public Mouse {
	public:
		friend Event;
		MouseMove(const unsigned int x, const unsigned int y) : Mouse(), m_pos({x, y}) {}
		const std::pair<unsigned int, unsigned int>& pos() const { return m_pos; }
		const unsigned int& x() const { return m_pos.first; }
		const unsigned int& y() const { return m_pos.second; }
	protected:
		MouseMove(const bool cast) : Mouse(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::MouseMove;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Mouse;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
		const std::pair<unsigned int, unsigned int> m_pos;
	};

	class MouseScroll : public Mouse {
	public:
		friend Event;
		MouseScroll(const float& x, const float& y) : Mouse(), m_offset({ x, y }) {}
		const std::pair<float, float>& offset() const { return m_offset; }
		const float& x() const { return m_offset.first; }
		const float& y() const { return m_offset.second; }
	protected:
		MouseScroll(const bool cast) : Mouse(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::MouseScroll;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Mouse;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
		const std::pair<float, float> m_offset;
	};

}