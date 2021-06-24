#pragma once
#include "npch.h"

namespace Nova::var {

	class HashString {
	public:
		using Hash = unsigned int;

		static constexpr Hash value(const char* str) { return compute(str); }
		static constexpr Hash value(const std::string_view& str) { return value(str.data()); }

		constexpr HashString(const char* str) : string(str), val(compute(string)) {}
		constexpr HashString(const std::string_view& str) : HashString(str.data()) {}

		constexpr Hash value() const { return val; }

		constexpr operator Hash() const { return val; }
		constexpr operator const char* () const { return string; }
		constexpr bool operator==(const HashString& other) const { return val == other.val; }

	protected:
		const char* string;
		const Hash val;

		static constexpr Hash hash_offset = 2166136261u;
		static constexpr Hash hash_prime = 16777619u;

		static constexpr Hash compute(const char* str) noexcept {
			auto value = hash_offset;
			while (*str != 0) {
				value = (value ^ static_cast<Hash>(*(str++))) * hash_prime;
			}
			return value;
		}
	};
}

constexpr Nova::var::HashString operator"" _ns(const char* str, std::size_t) { return Nova::var::HashString{ str }; }