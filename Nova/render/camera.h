#pragma once
#include "npch.h"
#include "render.h"
#include "phys/lib.h"

namespace Nova {

	class NOVA_API Render::Camera {
	public:
		// class NOVA_API Perspective;

		mlb::vec3 pos{ 0.0f, 0.0f, 1.0f };
		mlb::vec3 rot{ -90.0f, 0.0f, 0.0f };
		const mlb::vec3& dir;
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

		Camera() : dir(m_dir) {}
		~Camera() {}
	protected:
		mlb::vec3 m_dir{ 0.0f, 0.0f, 0.0f };
		mlb::mat4 m_vp{ 1.0f }, m_view, m_projection;
		virtual void new_projection() = 0;
	};

}