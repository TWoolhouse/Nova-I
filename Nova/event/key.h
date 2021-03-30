#pragma once
#include "event.h"
#include "input/key.h"

namespace Nova::Event {

	class Key : public Event {
	public:
		friend Event;
		Key(const Input::Key& key) : Event(), m_key(key) {}
		const bool is(const Input::Key& key) const { return m_key == key; }
		const Input::Key& key() const { return m_key; }
	protected:
		Key(const bool cast) : Event(cast), m_key(Input::Key::None) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::Key;
		virtual const Nova::Event::Type& type() { return ET; }
		const Input::Key m_key;
	};

	class KeyPress : public Key {
	public:
		friend Event;
		KeyPress(const Input::Key& key, const unsigned int repeat) : Key(key), m_repeat(repeat) {}
		const unsigned int repeat() const { return m_repeat; }
	protected:
		KeyPress(const bool cast) : Key(cast), m_repeat(0) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::KeyPress;
		virtual const Nova::Event::Type& type() { return ET; }
		const unsigned int m_repeat;
	};

	class KeyRelease : public Key {
	public:
		friend Event;
		KeyRelease(const Input::Key& key) : Key(key) {}
	protected:
		KeyRelease(const bool cast) : Key(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::KeyRelease;
		virtual const Nova::Event::Type& type() { return ET; }
	};

}