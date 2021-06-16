#pragma once

#ifdef NOVA
#include "npch.h"
#include "application.h"

#ifdef NOVA_DEBUG
	int main(int argc, char const* argv[])
#else
#ifdef _WIN64
	int WinMain(int argc, char const* argv[])
#else
	int main(int argc, char const* argv[])
#endif // Platform
#endif // NOVA_DEBUG

{
	Nova::Application* app = Nova::Application::Create();
	while (app->active()) {
		app->main();
	}
	delete app;
	return 0;
}

#endif // NOVA
