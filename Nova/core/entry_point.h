#pragma once

#ifdef NOVA
#include "npch.h"
#include "application.h"

//extern Nova::Application* Nova::Application::Create();

int main(int argc, char const* argv[]) {
	Nova::Application* app = Nova::Application::Create();
	while (app->active()) {
		app->main();
	}
	delete app;
	return 0;
}

#endif // NOVA
