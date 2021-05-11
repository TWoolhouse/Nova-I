#pragma once
#include "npch.h"

namespace Nova::Asset {

	template<typename T, typename A, typename K>
	class NOVA_API Library {
	public:
		Library() {}

		const Star<A>& store(const K& key, const Star<A>& asset) { m_assets[key] = std::weak_ptr(asset); }
		const Star<A>& get(const K& key) const { return m_assets[key]; }
		const Star<A>& operator[](const K& key) const { return m_assets[key]; }
		void free(const K& key) const { m_assets.erase(key); }
		const Star<A> pop(const K& key) const {
			Star<A> v = get(key);
			free(key);
			return v;
		}
		//const Star<A> load(const K& key);
	protected:
		std::unordered_map<K, StarWeak<A>> m_assets;
	};

}