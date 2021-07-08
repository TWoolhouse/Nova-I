#pragma once
#include "variadics.h"

#define __COMBINE(x,y) x ## y
#define COMBINE(x,y) __COMBINE(x,y)

namespace Nova::var::__v_list {
	template <template<size_t> class Elm, size_t I>
	struct Generator {
		using pack = typename decltype(packer<typename Elm<I - 1>::Type>(typename Generator<Elm, I - 1>::pack{}));
	};
	template <template<size_t> class Elm>
	struct Generator<Elm, 0> {
		using pack = pack<>;
	};

	template <size_t C>
	struct Counter : public Counter<(C - 1)> { static constexpr size_t N = C; };
	template <> struct Counter<0> { static constexpr size_t N = 0; };

}

#define NovaVarTypeListNew(name, size) \
namespace __vc_list_##name { \
	constexpr size_t S = size; \
	::Nova::var::__v_list::Counter<0> Creator(::Nova::var::__v_list::Counter<0>); \
	template <size_t I> struct E; \
}

#define NovaVarTypeList(name, type) \
namespace __vc_list_##name { \
	template <> struct E<decltype(Creator(::Nova::var::__v_list::Counter<S>{}))::N > { \
		using Type = type; \
	}; \
	::Nova::var::__v_list::Counter<decltype(Creator(::Nova::var::__v_list::Counter<S>{}))::N + 1 > Creator(::Nova::var::__v_list::Counter<decltype(Creator(::Nova::var::__v_list::Counter<S>{}))::N + 1 > ); \
}

#define NovaVarTypeListFin(name) \
using name = typename ::Nova::var::__v_list::Generator<__vc_list_##name##::E, decltype(__vc_list_##name##::Creator(::Nova::var::__v_list::Counter<__vc_list_##name##::S>{}))::N>::pack;
