#include "npch.h"
#include "ortho.h"

namespace Nova::Camera {

	void Ortho::make_projection() {
		m_projection = mlb::ortho(-1.0, 1.0, -1.0, 1.0);
	}

}