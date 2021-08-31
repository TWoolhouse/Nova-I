#pragma once
#include "variadics.h"

#define __COMBINE(x,y) x ## y
#define COMBINE(x,y) __COMBINE(x,y)

#define __STR(x) #x
#define STR(x) __STR(x)

namespace Nova::var {
	template <size_t C>
	struct Counter : public Counter<(C - 1)> { static constexpr size_t N = C; };
	template <> struct Counter<0> { static constexpr size_t N = 0; };
}

namespace Nova::var::__v_tlist {
	template <template<size_t> class Elm, size_t I>
	struct Generator {
		using pack = typename decltype(packer<typename Elm<I - 1>::Type>(typename Generator<Elm, I - 1>::pack{}));
	};
	template <template<size_t> class Elm>
	struct Generator<Elm, 0> {
		using pack = pack<>;
	};

}
// Create Pack Type List with maximum size
#define NovaVarTypeListNew(name, size) \
namespace __vc_list_::_##name { \
	constexpr size_t S = size; \
	::Nova::var::Counter<0> Creator(::Nova::var::Counter<0>); \
	template <size_t I> struct E; \
}

// Append Type to Pack List
#define NovaVarTypeList(name, type) \
namespace __vc_list_::_##name { \
	template <> struct E<decltype(Creator(::Nova::var::Counter<S>{}))::N > { \
		using Type = type; \
	}; \
	::Nova::var::Counter<decltype(Creator(::Nova::var::Counter<S>{}))::N + 1 > Creator(::Nova::var::Counter<decltype(Creator(::Nova::var::Counter<S>{}))::N + 1 > ); \
}

// Close Pack Type List
#define NovaVarTypeListFin(name) \
using name = typename ::Nova::var::__v_tlist::Generator<__vc_list_::_##name##::E, decltype(__vc_list_::_##name##::Creator(::Nova::var::Counter<__vc_list_::_##name##::S>{}))::N>::pack;
