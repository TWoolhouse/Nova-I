#pragma once
#include "npch.h"
#include "util/variadics.h"
#include "util/hashing.h"
#include <concepts>

namespace Nova {

	namespace Resource {
		template<typename T> concept Assetable = (requires (T a) {T::LibCreate;})
			&& std::is_same_v<typename var::signature<decltype(T::LibCreate)>::ret, Star<T>>;
		template<Assetable T> class Library;
	}

	template<Resource::Assetable T>
	class Asset {
		friend class Resource::Library<T>;
		using Key = var::HashString::Hash;
		using Creator = typename var::signature<decltype(T::LibCreate)>::decay::tuple;
	public:
		Asset() = default;
		// Const Asset Never Expires
		Asset(const Star<T>& star) : m_key(make_key_c(0)), ptr(star), creator() { constant.emplace_front(star); }
		Asset(const Key& key, const Star<T>& ptr, Creator args) : m_key(make_key_v(key)), ptr(ptr), creator(args) {}
		Asset(const Key& key, Creator args) : m_key(make_key_v(key)), ptr(), creator(args) {}
		//Asset(const Key& key, Creator args) : m_key(make_key_v(key)), ptr(), creator(args) {}
		~Asset() { if (is_key_c()) remove_const(ptr.lock()); }
		Asset& operator=(const Star<T>& asset) { star(asset); return *this; }

		Asset(const Asset& other) : m_key(other.m_key), ptr(other.ptr), creator(creator) {
			if (is_key_c())
				constant.emplace_front(ptr.lock());
		}
		Asset& operator=(const Asset& other) {
			m_key = other.m_key;
			ptr = other.ptr;
			creator = other.creator;
			if (is_key_c())
				constant.emplace_front(ptr.lock());
			return *this;
		}

		Asset& operator=(Asset&& other) {
			if (this == &other)	return *this;
			m_key = std::move(other.m_key);	other.m_key = 1;
			ptr = std::move(other.ptr);
			creator = std::move(other.creator);
		}
		Asset(Asset&& other) : m_key(std::move(other.m_key)), ptr(std::move(other.ptr)), creator(std::move(other.creator)) {
			other.m_key = 1;
		}

		const Key& key() const { return m_key; }
		operator Key() const { return m_key; }
		operator Star<T>() const { return get(); }
		Star<T> operator*() const { return get(); }
		Star<T> operator->() const { return get(); }

		Star<T> get() const {
			if (!ptr.expired())
				return ptr.lock();
			Star<T> star = load(creator);
			const_cast<Asset<T>*>(this)->ptr = star;
			return star;
		}

		Star<T>& star(const Star<T>& pointer) {
			nova_assert(is_key_c(), "Can only change constant asset pointers");
			auto it = std::find(constant.begin(), constant.end(), ptr.lock());
			ptr = *it = pointer;
			return *it;
			//return constant.emplace_front(ptr.lock());
		}

		Star<T>& permanent() {
			m_key = make_key_c(m_key);
			return constant.emplace_front(get());
		}

	protected:
		Key m_key;
		StarWeak<T> ptr;
		Creator creator;

		inline static std::forward_list<Star<T>> constant = {};

		constexpr static inline Key make_key_v(const Key& key) { return (key & ~1) + 1; }
		constexpr static inline Key make_key_c(const Key& key) { return key & ~1; }
		constexpr inline bool is_key_c() { return (!(m_key & 1)); }

		bool remove_const(const Star<T>& equal) {
			auto oit = constant.before_begin(), it = std::next(oit);
			while (it != constant.cend()) {
				if (*it == equal) {
					constant.erase_after(oit);
					return true;
				}
				oit = it++;
			}
			return false;
		}

		template<typename ...Args, std::size_t ...S>
		Star<T> load(const std::tuple<Args...>& tuple, std::index_sequence<S...>) const {
			return T::LibCreate(std::get<S>(tuple)...);
		}
		template<typename ...Args>
		Star<T> load(const std::tuple<Args...>& tuple) const {
			return load(tuple, std::index_sequence_for<Args...>{});
		}

	};

}