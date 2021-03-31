#define NOVA
#include <nova.h>
#include <iostream>

void t() {

}

class Sol : public Nova::Application {
public:
	virtual void update() override {
		std::cout << frame++ << std::endl;
	}
	virtual void event(Nova::Event::Event& event) override {
		if (auto e = event.cast<Nova::Event::KeyPress>())
			if (e.match(Nova::Input::Key::ESCAPE)) {
				Nova::Event::WindowClose close;
				event_callback(close);
		}
	}
private:
	unsigned int frame = 0;

};

Nova::Application* Nova::Application::Create() {
	return new Sol();
}