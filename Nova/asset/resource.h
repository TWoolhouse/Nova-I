#pragma once
#include "npch.h"
#include "type.h"
#include "util/variadics.h"
#include "util/hashing.h"

namespace Nova::Resource {

	//template<typename T>
	//class Library;

	//template<typename T>
	//class Base {
	//	friend class Asset<T>;
	//protected:
	//	static Star<T> LibCreate() = delete;
	//};

	template<typename T>
	class Library {
		using Key = var::HashString::Hash;
	public:
		Library() {}
		//Asset<T>& create(const Key& key, Args... args) {
		//	return m_assets.emplace(key, Asset<T>(key, Asset<T>::Creator(args...)));
		//}
		template<typename ...Args>
		Asset<T>& create(const Key& key, Args... args) {
			return m_assets.emplace(key, Asset<T>(key, Asset<T>::Creator(args...)));
		}
		Star<T> get(const Key& key) {
			return m_assets[key].get();
		}
		inline Star<T> operator[](const Key& key) { return get(key); }

		void clear() { m_assets.clear(); }
	protected:
		std::unordered_map<Key, Asset<T>> m_assets;
	};

}