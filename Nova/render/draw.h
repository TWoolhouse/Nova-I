#pragma once
#include "npch.h"
#include "render_state.h"
#include "phys/maths.h"
#include "texture.h"

namespace Nova {

	class NOVA_API Draw {
	public:
		inline static void Quad(const mlb::vec2& pos, const mlb::vec2& size, const float rot = 0) { return Quad(mlb::vec3{ pos, 0.0f }, size, rot); }
		inline static void Quad(const mlb::vec3& pos, const mlb::vec2& size, const float rot = 0) { return Quad(gen_mat(pos, size, rot)); }
		inline static void Quad(const mlb::mat4& mat) { return Quad(mat, mlb::vec4{1.0f}); }

		inline static void Quad(const mlb::vec2& pos, const mlb::vec2& size, const mlb::vec4& col, const float rot = 0) { return Quad(mlb::vec3{ pos, 0.0f }, size, col, rot); }
		inline static void Quad(const mlb::vec3& pos, const mlb::vec2& size, const mlb::vec4& col, const float rot = 0) { return Quad(gen_mat(pos, size, rot), col); }
		inline static void Quad(const mlb::mat4& mat, const mlb::vec4& col) { return Quad(mat, col, RenderState::Get().blank_texture); }

		inline static void Quad(const mlb::vec2& pos, const mlb::vec2& size, const Star<Texture2D>& texture, const float rot = 0) { return Quad(mlb::vec3{ pos, 0.0f }, size, texture, rot); }
		inline static void Quad(const mlb::vec3& pos, const mlb::vec2& size, const Star<Texture2D>& texture, const float rot = 0) { return Quad(gen_mat(pos, size, rot), texture); }
		inline static void Quad(const mlb::mat4& mat, const Star<Texture2D>& texture) { return Quad(mat, mlb::vec4{1.0f}, texture); }

		inline static void Quad(const mlb::vec2& pos, const mlb::vec2& size, const Texture2D::Sub& texture, const float rot = 0) { return Quad(mlb::vec3{ pos, 0.0f }, size, texture, rot); }
		inline static void Quad(const mlb::vec3& pos, const mlb::vec2& size, const Texture2D::Sub& texture, const float rot = 0) { return Quad(gen_mat(pos, size, rot), texture); }
		inline static void Quad(const mlb::mat4& mat, const Texture2D::Sub& texture) { return Quad(mat, mlb::vec4{1.0f}, texture); }

		inline static void Quad(const mlb::vec2& pos, const mlb::vec2& size, const mlb::vec4& col, const Star<Texture2D>& texture, const float rot = 0) { return Quad(mlb::vec3{ pos, 0.0f }, size, texture, rot); }
		inline static void Quad(const mlb::vec3& pos, const mlb::vec2& size, const mlb::vec4& col, const Star<Texture2D>& texture, const float rot = 0) { return Quad(gen_mat(pos, size, rot), texture); }
		inline static void Quad(const mlb::mat4& mat, const mlb::vec4& col, const Star<Texture2D>& texture) { return Quad(mat, col, texture, s_quad_tex_pos); }

		inline static void Quad(const mlb::vec2& pos, const mlb::vec2& size, const mlb::vec4& col, const Texture2D::Sub& texture, const float rot = 0) { return Quad(mlb::vec3{ pos, 0.0f }, size, col, texture, rot); }
		inline static void Quad(const mlb::vec3& pos, const mlb::vec2& size, const mlb::vec4& col, const Texture2D::Sub& texture, const float rot = 0) { return Quad(gen_mat(pos, size, rot), col, texture); }
		inline static void Quad(const mlb::mat4& mat, const mlb::vec4& col, const Texture2D::Sub& texture) { return Quad(mat, col, texture.texture(), texture.positions()); }

		static void Quad(const mlb::mat4& mat, const mlb::vec4& col, const Star<Texture2D>& texture, const std::array<mlb::vec2, 4>& tex_pos);

	protected:
		friend class RenderState;
		static const std::array<mlb::vec2, 4> s_quad_tex_pos;

		inline static mlb::mat4 gen_mat(const mlb::vec3& position, const mlb::vec2& size, const float rotation) {
			return mlb::rotate(mlb::scale(mlb::translate(mlb::mat4{ 1.0f }, position), { size, 0.0f }), mlb::radians(rotation), { 0.0f, 0.0f, 1.0f });
		}
	};

}