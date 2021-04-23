#pragma once

#ifdef NOVA_EXPORT
#define NOVA_API __declspec(dllexport)
#else
#define NOVA_API __declspec(dllimport)
#endif // NOVA_EXPORT

#include <string>
#include <utility>
#include <functional>
#include <vector>
#include <array>
#include <memory>
#include <cassert>
#include <variant>
#include <type_traits>