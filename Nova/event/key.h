#pragma once
#include "event.h"
#include "input/poll.h"

namespace Nova::Event {

	class Key : public Event {
	public:
		friend Event;
		Key(const Input::Key& key) : Event(), m_key(key) {}
		const bool match(const Input::Key& key) const { return m_key == key; }
		const Input::Key& key() const { return m_key; }
	protected:
		Key(const bool cast) : Event(cast), m_key(Input::Key::None) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::Key;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Key;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
		const Input::Key m_key;
	};

	class KeyPress : public Key {
	public:
		friend Event;
		KeyPress(const Input::Key& key, const unsigned int repeat = 0) : Key(key), m_repeat(repeat) {
			Input::State::set(key, true);
		}
		const unsigned int repeat() const { return m_repeat; }
	protected:
		KeyPress(const bool cast) : Key(cast), m_repeat(0) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::KeyPress;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Key;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
		const unsigned int m_repeat;
	};

	class KeyRelease : public Key {
	public:
		friend Event;
		KeyRelease(const Input::Key& key) : Key(key) {
			Input::State::set(key, false);
		}
	protected:
		KeyRelease(const bool cast) : Key(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::KeyRelease;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::Key;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
	};

}