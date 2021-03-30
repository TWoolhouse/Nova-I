#define NOVA
#include <nova.h>
#include <iostream>

class Sol : public Nova::Application {
};

Nova::Application* Nova::Create() {
	return new Sol();
}