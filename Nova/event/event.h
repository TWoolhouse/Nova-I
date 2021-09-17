#pragma once
#include "npch.h"
#include "type.h"
#include "util/variadics.h"

namespace Nova::Event {

	class NOVA_API Event {
	public:
		bool done = false;

		template<typename T>
		const bool is(const bool handle = true) {
			if (type() == T::ET) {
				done = handle;
				return true;
			} return false;
		}

		template<typename T>
		const bool cat(const bool handle = true) {
			if (tcat() == T::ETC) {
				done = handle;
				return true;
			} return false;
		}

		template<typename T>
		T cast(bool handle = true) {
			if (type() == T::ET) {
				done = handle;
				return static_cast<T&>(*this);
			}
			return T(false);
		}

		//template<typename T>
		//const bool dispatch(const bool (&func)(const T&)) {
		//	if (type() == T::ET)
		//		done = func(*static_cast<T*>(this));
		//	return done;
		//}
		template<typename T, typename F>
		const bool dispatch(const F& func) {
			if (type() == T::ET)
				done = func(*static_cast<T*>(this));
			return done;
		}

		inline explicit operator bool() const {
			return m_cast;
		}

	protected:
		Event(const bool cast = true) : m_cast(cast) {}
		constexpr static Nova::Event::Type ET = Nova::Event::Type::None;
		constexpr static Nova::Event::Type ETC = Nova::Event::Type::None;
		virtual const Nova::Event::Type& type() { return ET; }
		virtual const Nova::Event::Type& tcat() { return ETC; }
		bool m_cast = true;
	};

}