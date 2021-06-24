#pragma once
#include "npch.h"
#include "render.h"
#include "phys/lib.h"

namespace Nova {

	class NOVA_API Render::Camera {
	public:

		mlb::vec3 pos{ 0.0f, 0.0f, 1.0f };
		mlb::vec3 rot{ -90.0f, 0.0f, 0.0f };
		const mlb::vec3& dir;

		Camera(const float& width, const float& height, const float& near, const float& far, const float& zoom = 1.0f)
			: dir(m_dir), m_width(width), m_height(height), m_aspect(m_width / m_height), m_zoom(zoom), m_near(near), m_far(far) {}
		~Camera() {}

		const mlb::mat4& matrix() const { return m_vp; }
		const mlb::mat4& compute() {

			// Compute Directional Vector
			const auto& rx = mlb::radians(rot.x);
			const auto& ry = mlb::radians(rot.y);
			const auto& rz = mlb::radians(rot.z);
			const auto& cry = cos(ry);

			m_dir.x = cos(rx) * cry;
			m_dir.y = sin(ry);
			m_dir.z = sin(rx) * cry;

			m_view = mlb::lookAt(pos, pos + m_dir, { -sin(rz), cos(rz), 0.0f });
			// Do not recompute every frame
			new_projection();

			m_vp = m_projection * m_view;
			return m_vp;
		}

		const mlb::vec2 size() const { return { m_width, m_height }; }
		void size(const float width, const float height) {
			m_width = width;
			m_height = height;
			m_aspect = m_width / m_height;
			new_projection();
		}

		const float& zoom() { return m_zoom; }
		virtual void zoom(const float& value) { m_zoom = std::max(0.0f, m_zoom - value); }

	protected:
		mlb::vec3 m_dir{ 0.0f, 0.0f, 0.0f };
		mlb::mat4 m_vp{ 1.0f }, m_view, m_projection;
		float m_width, m_height, m_aspect, m_zoom, m_near, m_far;
		virtual void new_projection() = 0;
	};

}