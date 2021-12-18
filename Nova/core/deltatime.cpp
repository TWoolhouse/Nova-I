#include "npch.h"
#include "deltatime.h"
#include <chrono>

constexpr double s_physics_dt = 1.0f / 240.0f;

namespace Nova {
	constexpr const double DeltaTime::phys() {
		return s_physics_dt;
	}
}

#ifdef NOVA_OPENGL // OpenGL
#include <GLFW/glfw3.h>
double time_prev = 0, time_now = 0, time_dt = 0;

namespace Nova {
	const double DeltaTime::dt() {
		return time_dt;
	}
	void DeltaTime::update() {
		time_prev = time_now;
		time_now = glfwGetTime();
		time_dt = time_now - time_prev;
	}
	const double DeltaTime::time() {
		return time_now;
	}
}

#else
typedef std::chrono::steady_clock Clock;
typedef std::chrono::duration<double> fsec;
std::chrono::time_point<Clock, fsec> time_prev, time_now;
double time_dt = fsec(time_now - time_now).count();

namespace Nova {
	const double DeltaTime::dt() {
		return time_dt;
	}
	void DeltaTime::update() {
		time_prev = time_now;
		time_now = Clock::now();
		time_dt = fsec(time_now - time_prev).count();
	}
	const double DeltaTime::time() {
		return fsec(time_now).count();
	}
}
#endif // Clock Implementation