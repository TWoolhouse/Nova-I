#pragma once
#include "npch.h"
#include "util/variadics.h"
#include "util/hashing.h"

namespace Nova::Asset {

	template<typename T>
	class Library;

	template<typename T>
	class Base {
		friend class Library<T>;
	protected:
		static Star<T> LibCreate() = delete;
	private:
		
	};

	template<typename T>
	class Library {
		using Key = var::HashString::Hash;
		using Creator = typename var::signature<decltype(T::LibCreate)>::decay::tuple;
		using Value = std::pair<StarWeak<T>, Creator>;
	public:
		Library() {}
		template<typename ...Args>
		void record(const Key& key, Args... args) {
			m_assets.emplace(key, std::make_pair(nullptr, std::make_tuple(args...)));
		}
		template<typename ...Args>
		Star<T> create(const Key& key, Args... args) {
			Star<T> ptr = load(args...);
			m_assets.emplace(key, std::make_pair(ptr, std::make_tuple(args...)));
			return ptr;
		}
		Star<T> get(const Key& key) {
			auto& [weak, creator] = m_assets[key];
			if (!weak.expired())
				return weak.lock();
			Star<T> ptr = load(creator);
			weak = ptr;
			return ptr;
		}
		inline Star<T> operator[](const Key& key) { return get(key); }

		void clear() { m_assets.clear(); }
	protected:
		template<typename ...Args>
		Star<T> load(const std::tuple<Args...>& tuple) {
			return load(tuple, std::index_sequence_for<Args...>{});
		}
		template<typename ...Args, std::size_t ...S>
		Star<T> load(const std::tuple<Args...>& tuple, std::index_sequence<S...>) {
			return load(std::forward(std::get<S>(tuple))...);
		}
		template<typename ...Args>
		Star<T> load(Args&& ...args) {
			return T::LibCreate(args...);
		}
		std::unordered_map<Key, Value> m_assets;
	};

}