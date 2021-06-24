#pragma once
#include "npch.h"
#include "../camera.h"

namespace Nova::Camera {

	class Ortho : public Render::Camera {
	public:
		Ortho(const float& width, const float& height, const float& near = 0.1f, const float& far = 100.0f)
			: Render::Camera(width, height, near, far) { new_projection(); }
		virtual ~Ortho() {}

	protected:
		virtual void new_projection() override {
			m_projection = mlb::ortho(-m_aspect * m_zoom, m_aspect * m_zoom, -m_zoom, m_zoom, m_near, m_far);
		}
	};

}