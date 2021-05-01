#pragma once
#include "npch.h"
#include "render/camera.h"

namespace Nova::Camera {

	class NOVA_API Ortho : public Render::Camera {
	public:
		Ortho() : Render::Camera() {}
		virtual ~Ortho() {}
	protected:
		virtual void make_projection() override;
	};

}