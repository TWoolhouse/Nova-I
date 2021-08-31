#pragma once
#include "spch.h"

#ifdef NOVA
#include <nova.h>
#include "core/app.h"

#ifdef SOL_EDITOR

Nova::Application* Nova::Application::Create() {
	return new Sol::App();
}

#else // SOL_RUNTIME
class Flare;
// Inside the Flare
#include "core/flare.h"

Nova::Application* Nova::Application::Create() {
	return new Flare;
}

#endif // SOL_EDITOR

#endif // NOVA