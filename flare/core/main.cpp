#include "fpch.h"
#define NOVA
#include <nova.h>
#include <sol.h>

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
