#pragma once
#include "npch.h"
#include "event/key.h"
#include "input/poll.h"
#include "event/mouse.h"
#include "render/camera.h"
#include "core/deltatime.h"

namespace Nova::sol {

	class Camera {
	public:
		float speed = 2.0f;

		Camera(Render::Camera* camera) : camera(camera) {}
		void update() {
			const auto& dt = DeltaTime::dt();
			auto rate = speed * dt;
			if (Input::Poll(Input::Key::LSHIFT))
				rate *= 2.5;

			if (Input::Poll(Input::Key::W))
				camera->pos.y += rate;
			if (Input::Poll(Input::Key::S))
				camera->pos.y -= rate;
			if (Input::Poll(Input::Key::A))
				camera->pos.x -= rate;
			if (Input::Poll(Input::Key::D))
				camera->pos.x += rate;
		}
		void event(Event::Event& event) {
			if (auto e = event.cast<Event::MouseScroll>()) {
				const auto& off = e.offset().second;
				if (Input::Poll(Input::Key::LSHIFT))
					return camera->zoom(off * 0.5);
				return camera->zoom(off * 0.25);
			}
		}
	protected:
		Render::Camera* camera;
	};

}