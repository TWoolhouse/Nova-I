#pragma once
#include "npch.h"

namespace Nova::var {

	template<typename Base, typename ...T>
	inline constexpr auto all_base_of() {
		return (std::is_base_of<Base, T>::value && ...);
	}

	template<typename T, typename ...Ts>
	inline constexpr auto all_same() {
		return (std::is_same<T, Ts>::value && ...);
	}

	template<size_t Count, typename ...Ts>
	inline constexpr bool count() {
		if constexpr (sizeof...(Ts) >= Count)
			return true;
		return false;
	}

	struct none {};

	template<typename ...Ts>
	struct pack {
		using tuple = std::tuple<Ts...>;
	};

	template<typename T, typename ...Ts>
	pack<Ts..., T> packer(pack<Ts...>);

	template<typename ...Ts>
	struct decay : public pack<std::decay_t<Ts> ...> {};

	template<typename Sig> struct signature;
	template<typename R, typename ...Args> struct signature<R(Args...)> : public pack<Args...> {
		using decay = var::decay<Args...>;
		using ret = R;
	};

	//template<typename ...T>
	//struct repeat {
	//	template<typename ...R>
	//	inline static constexpr auto all() {
	//		static_assert(!(sizeof...(R) % sizeof...(T)), "Invalid number of Type arguments");
	//		if constexpr (sizeof...(R) == sizeof...(T))
	//			return (std::is_same<T, R>::value && ...);
	//		return repeat<T...>::all<R>()
	//	}
	//};

}