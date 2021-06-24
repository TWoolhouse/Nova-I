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
#include <unordered_map>

// #define NOVA_DEBUG
// #define NOVA_INTERNAL
// #define NOVA_RELEASE

 #define SOL_EDITOR
// #define SOL_RUNTIME

#if defined(SOL_EDITOR) && defined(SOL_RUNTIME)
#error Multiple Sol runtime requirements
#endif
