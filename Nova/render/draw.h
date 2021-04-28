#pragma once
#include "npch.h"
#include "render.h"

namespace Nova {

	class Render::Draw {
	public:
		inline static void Quad(const mlb::vec2& pos, const mlb::vec2& size, const float rot = 0) { return Quad(mlb::vec3{ pos, 0.0f }, size, rot); }
		inline static void Quad(const mlb::vec3& pos, const mlb::vec2& size, const float rot = 0) { return Quad(gen_mat(pos, size, rot)); }
		inline static void Quad(const mlb::mat4& mat) { return Quad(mat, s_colour); }

		inline static void Quad(const mlb::vec2& pos, const mlb::vec2& size, const mlb::vec4& col, const float rot = 0) { return Quad(mlb::vec3{ pos, 0.0f }, size, col, rot); }
		inline static void Quad(const mlb::vec3& pos, const mlb::vec2& size, const mlb::vec4& col, const float rot = 0) { return Quad(gen_mat(pos, size, rot), col); }
		static void Quad(const mlb::mat4& mat, const mlb::vec4& col);

	protected:
		static GLM_CONSTEXPR const mlb::vec4 s_colour{ 1.0f, 1.0f, 1.0f, 1.0f };

		inline static mlb::mat4 gen_mat(const mlb::vec3& position, const mlb::vec2& size, const float rotation) {
			return mlb::rotate(mlb::scale(mlb::translate(mlb::mat4{ 1.0f }, position), { size, 0.0f }), mlb::radians(rotation), { 0.0f, 0.0f, 1.0f });
		}
	};

}