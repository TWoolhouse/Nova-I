#include "npch.h"
#include "deltatime.h"
#include <chrono>

constexpr float s_physics_dt = 1.0f / 240.0f;
typedef std::chrono::steady_clock Clock;
typedef std::chrono::duration<float> fsec;
std::chrono::time_point<Clock, fsec> time_prev, time_now;
float time_dt = fsec(time_now - time_now).count();

namespace Nova {

	inline const float DeltaTime::dt() {
		return time_dt;
	}

	inline constexpr const float DeltaTime::phys() {
		return s_physics_dt;
	}

	inline void DeltaTime::update() {
		time_prev = time_now;
		time_now = Clock::now();
		time_dt = fsec(time_now - time_prev).count();
	}

}