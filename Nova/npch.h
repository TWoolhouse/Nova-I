#pragma once

#ifdef NOVA_EXPORT
#define NOVA_API __declspec(dllexport)
#else
#define NOVA_API __declspec(dllimport)
#endif // NOVA_EXPORT

#include <string>
#include <utility>
#include <functional>