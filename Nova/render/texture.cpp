#include "npch.h"
#include "texture.h"

namespace Nova {

	Texture2D::Sub::Sub(const Star<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_texture(texture) {
		m_pos[0] = min;
		m_pos[1] = { max.x, min.y };
		m_pos[2] = { min.x, max.y };
		m_pos[3] = max;
	}
	Texture2D::Sub::Sub(const Star<Texture2D>& texture, const glm::vec2& pos, const glm::vec2& size, const glm::vec2& grid)
		: Sub(texture,
			glm::vec2((pos * grid) / texture->size()),
			glm::vec2(((pos + size) * grid) / texture->size())
		) {}

	Texture2D::Sub Texture::Atlas::subtexture(const glm::vec2& pos, const glm::vec2& size) const {
		return { m_texture, pos, size, m_grid };
	}

}