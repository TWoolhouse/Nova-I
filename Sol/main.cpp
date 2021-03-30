#define NOVA
#include <nova.h>
#include <iostream>

void t() {

}

class Sol : public Nova::Application {
};

Nova::Application* Nova::Application::Create() {
	return new Sol();
}