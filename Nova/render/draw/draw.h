#pragma once
#include "npch.h"
#include "asset/stock.h"
#include "../draw.h"

namespace Nova::RenderDraw {

	class Draw {
	public:
		static void Initialise() { nova_assert(false, "Abstract Class"); }
		static void Terminate() { nova_assert(false, "Abstract Class"); }
		static void Flush() { nova_assert(false, "Abstract Class"); }
	};

	template<typename Drawer>
	class TextureMap {
	public:
		TextureMap(const unsigned int size) : m_size(size), m_bindings(size) {}

		void clear() {
			m_bindings.clear();
			m_bindings[Resource::Stock::Texture::blank] = 0;
		}

		void bind() {
			for (auto& tex : m_bindings) {
				tex.first->bind(tex.second);
			}
		}

		unsigned int index(const Star<Texture2D>& texture) {
			if (!texture)
				return 0;
			auto res = m_bindings.find(texture);
			if (res != m_bindings.cend()) {
				return res->second;
			} else {
				auto size = m_bindings.size();
				if (size >= m_size - 1) {
					Drawer::Flush();
					clear();
					size = 1;
				}
				m_bindings[texture] = size;
				return size;
			}
		}
	protected:
		const unsigned int m_size;
		std::unordered_map<Star<Texture2D>, unsigned int> m_bindings;
	};

}