#pragma once
#include "npch.h"
#include "render.h"
#include "phys/maths.h"

namespace Nova {

	class NOVA_API Render::Camera {
	public:
		// class NOVA_API Perspective;

		mlb::vec3 pos{ 0.0f };
		mlb::vec3 rot{ 0.0f };
		const mlb::mat4& matrix() const { return m_vp; }
		const mlb::mat4& compute() {
			m_view = mlb::inverse(mlb::rotate(mlb::translate(mlb::mat4(1.0f), pos), rot.z, { 0, 0, 1 } ));

			m_vp = m_projection * m_view;
			return m_vp;
		}

		~Camera() {}
	protected:
		mlb::mat4 m_vp{ 1.0f }, m_view, m_projection;
		virtual void make_projection() = 0;
	};

}