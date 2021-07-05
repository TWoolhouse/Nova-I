#pragma once
#include "npch.h"

namespace Nova::var {

	class HashString {
	public:
		using Hash = unsigned int;

		static constexpr Hash value(cstring str) { return compute(str); }
		static constexpr Hash value(const std::string_view& str) { return value(str.data()); }

		constexpr HashString(cstring str) : string(str), val(compute(string)) {}
		constexpr HashString(const std::string_view& str) : HashString(str.data()) {}

		constexpr Hash value() const { return val; }

		constexpr operator Hash() const { return val; }
		constexpr operator cstring () const { return string; }
		constexpr bool operator==(const HashString& other) const { return val == other.val; }

	protected:
		cstring string;
		const Hash val;

		static constexpr Hash hash_offset = 2166136261u;
		static constexpr Hash hash_prime = 16777619u;

		static constexpr Hash compute(cstring str) noexcept {
			auto value = hash_offset;
			while (*str != 0) {
				value = (value ^ static_cast<Hash>(*(str++))) * hash_prime;
			}
			return value;
		}
	};
}

constexpr Nova::var::HashString operator"" _ns(cstring str, std::size_t) { return Nova::var::HashString{ str }; }