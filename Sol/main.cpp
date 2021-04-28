#define NOVA
#include <nova.h>
#include <iostream>
#include "ants.h"

class Sol : public Nova::Application {
public:
	Sol() : bc(Nova::Buffer::Context::Create()) {
		Nova::Render::Command::VSync(true);

		float vb_data[] = {
			-1.0f,  1.0f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
			 1.0f,  1.0f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
			-1.0f, -1.0f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
			 1.0f, -1.0f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		};
		constexpr size_t ib_size = 6;
		unsigned int ib_data[ib_size] = {
			0, 1, 2, 2, 1, 3
		};

		auto vb = Nova::Buffer::Vertex::Create(sizeof(vb_data), vb_data);
		auto ib = Nova::Buffer::Index::Create(ib_size, ib_data);

		bc->buffer(ib);
		bc->buffer(vb, {
			{ Nova::Buffer::Type::Float2, "v_pos" },
			{ Nova::Buffer::Type::Float3, "v_col" },
			{ Nova::Buffer::Type::Float2, "v_tex" },
		});

		shader = Nova::Shader::Create("shader/simple.glsl");

		shader_buffer = Nova::Buffer::Shader::Create(shader, "test", {
			"mult",
			"buffer_colour",
		});

		constexpr float mult = 1.0;
		shader_buffer->set("mult", &mult);
		std::array<float, 3> shader_colour = {1.0f, 1.0f, 1.0f};
		shader_buffer->set("buffer_colour", shader_colour.data());

		ants = new Ants(128, 1280, 720);
	}

	~Sol() {
		delete ants;
	}

	virtual void update() override {
		//std::cout << Nova::DeltaTime::dt() * 1000 << std::endl;
		ants->update();

		for (int x = -10; x <= 10; ++x) {
			for (int y = -10; y <= 10; ++y) {
				Nova::Render::Draw::Quad(
					{ 0.1 * x, 0.1 * y },
					{ 0.05, 0.05 },
					{ (static_cast<float>(x + 10) / 20.0), (static_cast<float>(y + 10) / 20.0), 0.5, 1.0 },
					(x + y) * 18.0f
				);
			}
		}

		shader_buffer->bind(0);
		ants->get_texture()->bind();
		shader->bind();
		bc->bind();
		Nova::Render::Command::Draw(bc);
	}

	virtual void event(Nova::Event::Event& event) override {
		if (auto e = event.cast<Nova::Event::KeyPress>()) {
			if (e.match(Nova::Input::Key::ESCAPE)) {
				Nova::Event::WindowClose close;
				event_callback(close);
			}
		}
		ants->event(event);
	}

private:
	Nova::Buffer::Context* bc;
	Nova::Shader* shader;
	Nova::Buffer::Shader* shader_buffer;
	Ants* ants;
};

Nova::Application* Nova::Application::Create() {
	return new Sol();
}