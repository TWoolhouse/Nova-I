#define NOVA
#include <nova.h>
#include <iostream>

class Sol : public Nova::Application {
public:
	Sol() : bc(Nova::Buffer::Context::Create()) {

		float vb_data[] = {
			-0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
			 0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			-0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
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

		shader = Nova::Shader::Create("Nova/res/shader/simple.glsl");

		texture = Nova::Texture2D::Create("Nova/res/texture/test.jpg", {});

		shader_buffer = Nova::Buffer::Shader::Create(shader, "test", {
			"mult",
			"buffer_colour",
		});

		constexpr float mult = 1;
		shader_buffer->set("mult", &mult);
		std::array<float, 3> shader_colour = {0.0f, 0.0f, 1.0f};
		shader_buffer->set("buffer_colour", shader_colour.data());

		compute = Nova::ShaderCompute::Create("Nova/res/shader/compute.glsl", { 100, 100, 1 });
		compute_output = Nova::Texture2D::Create(100, 100, { Nova::Texture::Colour{Nova::Texture::Colour::Type::RGBAW, Nova::Texture::Colour::Type::RGBA} });
		compute->Upload()->Int("output_image", 0);
		compute_output->image(0);

		compute_shader_buffer = Nova::Buffer::Shader::Create(compute, "test", {
			"pray",
			"lol",
		});
		std::array<float, 100> arr;
		for (auto& i : arr) {
			i = 0;
		}
		compute_shader_buffer->set("pray", arr.data());

		std::array<float, 3> lol = { 1.0, 0.0, 0.0 };
		compute_shader_buffer->set("lol", lol.data());
	}

	virtual void update() override {
		static unsigned int frame = 0;
		if (Nova::Input::Poll(Nova::Input::Key::F)) {
			std::cout << frame++ << std::endl;
			float mult = frame / 100.0f;
			shader_buffer->set("mult", &mult);
		}

		compute->bind();
		compute_output->image(0);
		compute_shader_buffer->bind(1);
		compute->dispatch();

		//std::array<float, 100> out_data;
		//compute_shader_buffer->get("pray", out_data.data());
		//for (auto& i : out_data) {
		//	std::cout << i << " ";
		//} std::cout << std::endl;

		//compute_output->bind(0);
		compute_output->bind(0);
		shader_buffer->bind(0);
		shader->Upload()->Int("u_tex", 0);
		Nova::Render::Draw(bc, shader);
	}

	virtual void event(Nova::Event::Event& event) override {
		if (auto e = event.cast<Nova::Event::KeyPress>()) {
			if (e.match(Nova::Input::Key::ESCAPE)) {
				Nova::Event::WindowClose close;
				event_callback(close);
			} else if (e.match(Nova::Input::Key::S)) {
				bool b;
				compute_shader_buffer->get("v_colour_active", &b);
				b = !b;
				std::cout << b << std::endl;
				compute_shader_buffer->set("v_colour_active", &b);
			}
		}
	}

private:
	Nova::Buffer::Context* bc;
	Nova::Shader* shader;
	Nova::Texture2D* texture;
	Nova::Buffer::Shader* shader_buffer, *compute_shader_buffer;
	Nova::ShaderCompute* compute;
	Nova::Texture2D* compute_output;

};

Nova::Application* Nova::Application::Create() {
	return new Sol();
}