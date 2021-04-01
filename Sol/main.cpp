#define NOVA
#include <nova.h>
#include <iostream>

class Sol : public Nova::Application {
public:
	Sol() : bc(Nova::Buffer::Context::Create()) {
		float vb_data[] = {
			-0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
			 0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			-0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
			 0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
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

		shader = Nova::Shader::Create({
			Nova::ShaderSource::Create("Nova/res/shader/vertex.glsl"),
			Nova::ShaderSource::Create("Nova/res/shader/frag.glsl")
		});

		texture = Nova::Texture2D::Create("Nova/res/texture/shy_guy.jpg", {}, {});

	}

	virtual void update() override {
		static unsigned int frame = 0;
		if (Nova::Input::Poll(Nova::Input::Key::F))
			std::cout << frame++ << std::endl;

		texture->bind();
		Nova::Render::Draw(bc, shader);
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
	Nova::Shader* shader;
	Nova::Texture2D* texture;

};

Nova::Application* Nova::Application::Create() {
	return new Sol();
}