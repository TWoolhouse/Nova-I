#pragma once

#ifdef NOVA
#include "npch.h"
#include "application.h"

extern Nova::Application* Nova::Create();

int main(int argc, char const* argv[]) {
	Nova::Application* app = Nova::Create();
	while (app->active()) {

	}
	delete app;
	return 0;
}

#endif // NOVA
