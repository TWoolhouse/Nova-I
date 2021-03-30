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
		virtual const Nova::Event::Type& type() { return ET; }
	};

	class MouseButton : public Mouse {
	public:
		friend Event;
		MouseButton(const Input::Mouse& button) : Mouse(), m_button(button) {}
		const bool is(const Input::Mouse& button) const { return m_button == button; }
		const Input::Mouse& button() const { return m_button; }
	protected:
		MouseButton(const bool cast) : Mouse(cast), m_button(Input::Mouse::None) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::MouseButton;
		virtual const Nova::Event::Type& type() { return ET; }
		const Input::Mouse m_button;
	};

	class MouseButtonPress : public MouseButton {
	public:
		friend Event;
		MouseButtonPress(const Input::Mouse& button) : MouseButton(button) {}
	protected:
		MouseButtonPress(const bool cast) : MouseButton(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::MouseButtonPress;
		virtual const Nova::Event::Type& type() { return ET; }
	};

	class MouseButtonRelease : public MouseButton {
	public:
		friend Event;
		MouseButtonRelease(const Input::Mouse& button) : MouseButton(button) {}
	protected:
		MouseButtonRelease(const bool cast) : MouseButton(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::MouseButtonRelease;
		virtual const Nova::Event::Type& type() { return ET; }
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
		virtual const Nova::Event::Type& type() { return ET; }
		const std::pair<unsigned int, unsigned int> m_pos;
	};

	class MouseScroll : public Mouse {
	public:
		friend Event;
		MouseScroll(const unsigned int& x, const unsigned int& y) : Mouse(), m_offset({ x, y }) {}
		const std::pair<unsigned int, unsigned int>& offset() const { return m_offset; }
		const unsigned int& x() const { return m_offset.first; }
		const unsigned int& y() const { return m_offset.second; }
	protected:
		MouseScroll(const bool cast) : Mouse(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::MouseScroll;
		virtual const Nova::Event::Type& type() { return ET; }
		const std::pair<unsigned int, unsigned int> m_offset;
	};

}