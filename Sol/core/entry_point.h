#pragma once
#include "spch.h"

#ifdef SOL

#define NOVA
#include <nova.h>
#include "core/app.h"

#ifdef SOL_EDITOR

Nova::Application* Nova::Application::Create() {
	return new Sol::App();
}

#else

class Flare : public Nova::Application {
	
};

Nova::Application* Nova::Application::Create() {
	return new Flare;
}

#endif // SOL_EDITOR

#endif // SOL