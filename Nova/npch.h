#pragma once

#include <string>
#include <utility>
#include <functional>
#include <vector>
#include <array>
#include <memory>
#include <cassert>
#include <variant>
#include <type_traits>

#ifdef NOVA_EXPORT
#define NOVA_API __declspec(dllexport)
#else
#define NOVA_API __declspec(dllimport)
#endif // NOVA_EXPORT

namespace Nova {
	template<typename T>
	using Star = std::shared_ptr<T>;
	template<typename T>
	using StarWeak = std::weak_ptr<T>;
	template<typename T>
	using StarUnique = std::unique_ptr<T>;
}