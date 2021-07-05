#pragma once
#include "npch.h"
#include "render_state.h"
#include "phys/lib.h"
#include "texture.h"
#include "asset/stock.h"

namespace Nova {

	class NOVA_API Draw {
	public:
		inline static void Quad(const glm::vec2& pos, const glm::vec2& size, const float rot = 0) { return Quad(glm::vec3{ pos, 0.0f }, size, rot); }
		inline static void Quad(const glm::vec3& pos, const glm::vec2& size, const float rot = 0) { return Quad(gen_mat(pos, size, rot)); }
		inline static void Quad(const glm::mat4& mat) { return Quad(mat, glm::vec4{1.0f}); }

		inline static void Quad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& col, const float rot = 0) { return Quad(glm::vec3{ pos, 0.0f }, size, col, rot); }
		inline static void Quad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& col, const float rot = 0) { return Quad(gen_mat(pos, size, rot), col); }
		inline static void Quad(const glm::mat4& mat, const glm::vec4& col) { return Quad(mat, col, Resource::Stock::Texture::blank); }

		inline static void Quad(const glm::vec2& pos, const glm::vec2& size, const Star<Texture2D>& texture, const float rot = 0) { return Quad(glm::vec3{ pos, 0.0f }, size, texture, rot); }
		inline static void Quad(const glm::vec3& pos, const glm::vec2& size, const Star<Texture2D>& texture, const float rot = 0) { return Quad(gen_mat(pos, size, rot), texture); }
		inline static void Quad(const glm::mat4& mat, const Star<Texture2D>& texture) { return Quad(mat, glm::vec4{1.0f}, texture); }

		inline static void Quad(const glm::vec2& pos, const glm::vec2& size, const Texture2D::Sub& texture, const float rot = 0) { return Quad(glm::vec3{ pos, 0.0f }, size, texture, rot); }
		inline static void Quad(const glm::vec3& pos, const glm::vec2& size, const Texture2D::Sub& texture, const float rot = 0) { return Quad(gen_mat(pos, size, rot), texture); }
		inline static void Quad(const glm::mat4& mat, const Texture2D::Sub& texture) { return Quad(mat, glm::vec4{1.0f}, texture); }

		inline static void Quad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& col, const Star<Texture2D>& texture, const float rot = 0) { return Quad(glm::vec3{ pos, 0.0f }, size, col, texture, rot); }
		inline static void Quad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& col, const Star<Texture2D>& texture, const float rot = 0) { return Quad(gen_mat(pos, size, rot), col, texture); }
		inline static void Quad(const glm::mat4& mat, const glm::vec4& col, const Star<Texture2D>& texture) { return Quad(mat, col, texture, s_quad_tex_pos); }

		inline static void Quad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& col, const Texture2D::Sub& texture, const float rot = 0) { return Quad(glm::vec3{ pos, 0.0f }, size, col, texture, rot); }
		inline static void Quad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& col, const Texture2D::Sub& texture, const float rot = 0) { return Quad(gen_mat(pos, size, rot), col, texture); }
		inline static void Quad(const glm::mat4& mat, const glm::vec4& col, const Texture2D::Sub& texture) { return Quad(mat, col, texture.texture(), texture.positions()); }

		static void Quad(const glm::mat4& mat, const glm::vec4& col, const Star<Texture2D>& texture, const std::array<glm::vec2, 4>& tex_pos);

	protected:
		friend struct Render::RState;
		static const std::array<glm::vec2, 4> s_quad_tex_pos;

		inline static glm::mat4 gen_mat(const glm::vec3& position, const glm::vec2& size, const float rotation) {
			return glm::rotate(glm::scale(glm::translate(glm::mat4{ 1.0f }, position), { size, 0.0f }), glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
		}
	};

}