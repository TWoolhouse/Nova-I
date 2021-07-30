#pragma once

#include <npch.h>
#include <type_traits>
#include <numeric>
#include <memory>
#include <array>
#include <vector>
#include <string>
#include <bitset>
#include <variant>
#include <forward_list>
#include <unordered_map>
#include <utility>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#ifdef SOL_STATIC
#define SOL_API
#else
#ifdef SOL_EXPORT
#define SOL_API __declspec(dllexport)
#else
#define SOL_API __declspec(dllimport)
#endif // SOL_EXPORT
#endif // SOL_STATIC

// #define SOL_EDITOR
// #define SOL_RUNTIME

#if (!(defined(SOL_EDITOR) || defined(SOL_RUNTIME)))
#error No Sol runtime configuration
#endif
#if defined(SOL_EDITOR) && defined(SOL_RUNTIME)
#error Multiple Sol runtime configurations
#endif

namespace Sol {}