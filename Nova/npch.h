#pragma once

#include <string>
#include <utility>
#include <functional>
#include <vector>
#include <array>
#include <memory>
#include <variant>
#include <type_traits>
#include <bitset>

#ifdef NOVA_EXPORT
#define NOVA_API __declspec(dllexport)
#else
#define NOVA_API __declspec(dllimport)
#endif // NOVA_EXPORT

// #define NOVA_DEBUG
// #define NOVA_INTERNAL
// #define NOVA_RELEASE

#ifndef NOVA_RELEASE
#define nova_assert(flag, msg) _nova_assert(flag, msg)
void NOVA_API _nova_assert(const bool& flag, const std::string& msg);
#else
#define nova_assert(flag, msg) ((void)0);
#endif // NOVA_RELEASE

namespace Nova {
	template<typename T>
	using Star = std::shared_ptr<T>;
	template<typename T>
	using StarWeak = std::weak_ptr<T>;
	template<typename T>
	using StarUnique = std::unique_ptr<T>;
}