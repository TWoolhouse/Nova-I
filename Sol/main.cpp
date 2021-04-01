#define NOVA
#include <nova.h>
#include <iostream>

void t() {

}

class Sol : public Nova::Application {
public:
	Sol() : bc(Nova::Buffer::Context::Create()) {
		float vb_data[] = {
			 0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f
		};
		unsigned int ib_data[] = {
			0, 1, 2
		};

		auto vb = Nova::Buffer::Vertex::Create(sizeof(vb_data), vb_data);
		auto ib = Nova::Buffer::Index::Create(3, ib_data);

		bc->buffer(ib);
		bc->buffer(vb, {
			{ Nova::Buffer::Type::Float2, "v_pos" },
			{ Nova::Buffer::Type::Float3, "v_col" }
		});

		shader = Nova::ShaderPipeline::Create({
			Nova::Shader::Create("Nova/res/shader/vertex.glsl"),
			Nova::Shader::Create("Nova/res/shader/frag.glsl")
		});

	}

	virtual void update() override {
		static unsigned int frame = 0;
		if (Nova::Input::Poll(Nova::Input::Key::F))
			std::cout << frame++ << std::endl;

		shader->bind();
		Nova::Render::Command::Draw(bc);
	}

	virtual void event(Nova::Event::Event& event) override {
		if (auto e = event.cast<Nova::Event::KeyPress>())
			if (e.match(Nova::Input::Key::ESCAPE)) {
				Nova::Event::WindowClose close;
				event_callback(close);
		}
	}

private:
	Nova::Buffer::Context* bc;
	Nova::ShaderPipeline* shader;

};

Nova::Application* Nova::Application::Create() {
	return new Sol();
}