#pragma once
#include "spch.h"
#include <nova.h>

namespace Sol::Editor {

	class Camera {
	public:
		float speed = 2.0f;

		Camera(Nova::Render::Camera* camera) : camera(camera) {}
		void update() {
			const auto& dt = Nova::DeltaTime::dt();
			auto rate = speed * dt;
			if (Nova::Input::Poll(Nova::Input::Key::LSHIFT))
				rate *= 2.5;

			if (Nova::Input::Poll(Nova::Input::Key::W))
				camera->pos.y += rate;
			if (Nova::Input::Poll(Nova::Input::Key::S))
				camera->pos.y -= rate;
			if (Nova::Input::Poll(Nova::Input::Key::A))
				camera->pos.x -= rate;
			if (Nova::Input::Poll(Nova::Input::Key::D))
				camera->pos.x += rate;
		}
		void event(Nova::Event::Event& event) {
			if (auto e = event.cast<Nova::Event::MouseScroll>()) {
				const auto& off = e.offset().second;
				if (Nova::Input::Poll(Nova::Input::Key::LSHIFT))
					return camera->zoom(off * 0.5);
				return camera->zoom(off * 0.25);
			}
		}
	protected:
		Nova::Render::Camera* camera;
	};

}