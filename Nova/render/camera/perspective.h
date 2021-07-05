#pragma once
#include "npch.h"
#include "../camera.h"

namespace Nova::Camera {

	class Perspective : public Render::Camera {
	public:
		Perspective(const float fov, const float width, const float height, const float near = 0.1f, const float far = 100.0f)
			: Render::Camera(width, height, near, far), m_fov(glm::radians(fov)) { new_projection(); }
		virtual ~Perspective() {}

		virtual void zoom(const float value) { m_zoom = std::max(0.0f, std::min(m_zoom - value, Nova::glm::pi<float>() / m_fov)); }
	protected:
		float m_fov;
		virtual void new_projection() override {
			m_projection = glm::perspective(m_fov * m_zoom, m_aspect, m_near, m_far);
		}
	};

}