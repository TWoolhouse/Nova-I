#include "npch.h"
#include "ortho.h"

namespace Nova::Camera {

	void Ortho::new_projection() {
		m_projection = mlb::ortho(-m_aspect * m_zoom, m_aspect * m_zoom, -m_zoom, m_zoom, m_near, m_far);
	}

}