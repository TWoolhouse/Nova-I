#pragma once
#include "npch.h"
#include "../camera.h"

namespace Nova::Camera {

	class NOVA_API Ortho : public Render::Camera {
	public:
		Ortho(const float width, const float height, const float near = 0.1f, const float far = 100.0f)
			: Render::Camera(), m_width(width), m_height(height), m_near(near), m_far(far), m_aspect(m_width / m_height) { new_projection(); }
		virtual ~Ortho() {}

		void set(const float width, const float height) {
			m_width = width;
			m_height = height;
			m_aspect = m_width / m_height;
			new_projection();
		}
		const float& zoom() { return m_zoom; }
		void zoom(const float& value) { m_zoom = std::max(0.1f, m_zoom - value); }

	protected:
		float m_zoom = 1;
		float m_width, m_height, m_near, m_far;
		float m_aspect;
		virtual void new_projection() override;
	};

}