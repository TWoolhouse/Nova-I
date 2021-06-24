#include "spch.h"
#define NOVA
#include <nova.h>
#include "core/app.h"

Nova::Application* Nova::Application::Create() {
	return new Sol::App();
}
