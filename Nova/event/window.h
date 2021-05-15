#pragma once
#include "event.h"

namespace Nova::Event {

	class Window : public Event {
	public:
		friend Event;
		Window() : Event() {}
	protected:
		Window (const bool cast) : Event(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::Window;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Window;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
	};

	class WindowClose : public Window {
	public:
		friend Event;
		WindowClose() : Window() {}
	protected:
		WindowClose(const bool cast) : Window(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::WindowClose;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Window;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
	};

	class WindowFocus : public Window {
	public:
		friend Event;
		WindowFocus() : Window() {}
	protected:
		WindowFocus(const bool cast) : Window(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::WindowFocus;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Window;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
	};

	class WindowFocusLost : public WindowFocus {
	public:
		friend Event;
		WindowFocusLost() : WindowFocus() {}
	protected:
		WindowFocusLost(const bool cast) : WindowFocus(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::WindowFocusLost;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Window;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
	};

	class WindowFocusGain : public WindowFocus {
	public:
		friend Event;
		WindowFocusGain() : WindowFocus() {}
	protected:
		WindowFocusGain(const bool cast) : WindowFocus(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::WindowFocusGain;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Window;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
	};

	class WindowMove : public Window {
	public:
		friend Event;
		WindowMove(const unsigned int x, const unsigned int y) : Window(), m_pos({x, y}) {}
		const std::pair<unsigned int, unsigned int>& pos() const { return m_pos; }
		const unsigned int& x() const { return m_pos.first; }
		const unsigned int& y() const { return m_pos.second; }
	protected:
		WindowMove(const bool cast) : Window(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::WindowMove;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Window;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
		const std::pair<unsigned int, unsigned int> m_pos;
	};

	class WindowResize : public Window {
	public:
		friend Event;
		WindowResize(const unsigned int x, const unsigned int y) : Window(), m_dim({ x, y }) {}
		const std::pair<unsigned int, unsigned int>& size() const { return m_dim; }
		const unsigned int& x() const { return m_dim.first; }
		const unsigned int& y() const { return m_dim.second; }
	protected:
		WindowResize(const bool cast) : Window(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::WindowResize;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Window;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
		const std::pair<unsigned int, unsigned int> m_dim;
	};

}