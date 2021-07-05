#include "spch.h"
#include <nova.h>
#include <iostream>
#include <algorithm>
#include "ants.h"

struct AntProps {
	float fade = 1.5f, diffuse = 25.0f;
} s_properties;

Ants::Ants(const unsigned int blocks, const unsigned int width, const unsigned int height) {
	constexpr unsigned int width_unit = 64, height_unit = 18;
	constexpr unsigned int blocksize = 1024;

	nova_assert(!(width % width_unit), "Width must be a multiple of the width unit");
	nova_assert(!(height % height_unit), "Height must be a multiple of the height unit");
	m_texture = Nova::Texture2D::Create(width, height, {
		{Nova::Texture::Colour::Type::RGBA, Nova::Texture::Colour::Type::RGBAW },
		{},
		{Nova::Texture::Filtering::Type::Linear, Nova::Texture::Filtering::Type::Nearest},
		});
	m_agent = Nova::ShaderCompute::Create("asset/shader/trail.agent.glsl", { blocks, 1, 1 });
	m_agent->Upload()->Int("output_image", 0);
	m_agent->Upload()->Float("dt", 0.0f);

	m_buffer = Nova::Buffer::Shader::Create(m_agent, "data", {
		"steering",
		"scan_dist",
		"scan_angle",
		"colour",
		"agents",
		});

	m_fade = Nova::ShaderCompute::Create("asset/shader/trail.fade.glsl", { m_texture->size().x / 64, m_texture->size().y / 18, 1 });
	m_fade->Upload()->Int("output_image", 0);
	m_fade->Upload()->Float("u_fade", s_properties.fade);
	m_fade->Upload()->Float("u_diffuse", s_properties.diffuse);
	m_fade->Upload()->Float("dt", 0.0f);

	// Must be first
	m_buffer->set("agents", sizeof(Agent) * blocks * blocksize);

	float upload = 45.0f;
	m_buffer->set("scan_angle", &upload);
	upload = 50.0;
	m_buffer->set("scan_dist", &upload);
	upload = 0.1f;
	m_buffer->set("steering", &upload);

	const Nova::glm::vec4 colour = { 1.0, 1.0, 1.0, 1.0 };
	m_buffer->set("colour", &colour);

	std::vector<Agent> agents(blocksize);
	{
		unsigned int iterations = std::max(static_cast<unsigned int>(1), blocks / 100);
		float speed = 125.0f;
		const unsigned int x = m_texture->size().x / 2, y = m_texture->size().y / 2;
		auto rand_dir = Nova::glm::Random::generatorf<float>(0, 1);
		auto random = Nova::glm::Random::generatorf<float>(speed * 0.75, speed);

		auto random_w = Nova::glm::Random::generatorf<float>(0, width);
		auto random_h = Nova::glm::Random::generatorf<float>(0, height);

		std::cout << "Agents: " << std::endl;
		for (size_t i = 0; i < blocks; i++) {
			for (auto& agent : agents) {
				//agent.pos = { x, y };
				agent.pos = {
					random_w(Nova::glm::Random::generator()),
					random_h(Nova::glm::Random::generator()),
				};
				agent.vel = {
					random(Nova::glm::Random::generator()) * (rand_dir(Nova::glm::Random::generator()) < 0.5 ? 1 : -1),
					random(Nova::glm::Random::generator()) * (rand_dir(Nova::glm::Random::generator()) < 0.5 ? 1 : -1),
				};
			}
			m_buffer->set("agents", agents.data(), sizeof(Agent) * agents.size(), sizeof(Agent) * blocksize * i);
			m_buffer->sync();
			if (!(i % iterations)) std::cout << (100 * i) / blocks << " ";
		} std::cout << "Done!" << std::endl;
	}
}

void Ants::update() {
	m_agent->bind();
	m_agent->Upload()->Float("dt", Nova::DeltaTime());
	m_texture->image(0);
	m_buffer->bind(1);
	m_agent->dispatch();

	m_fade->bind();
	m_fade->Upload()->Float("dt", Nova::DeltaTime());
	m_fade->dispatch();
};

void Ants::event(Nova::Event::Event& event) {
	if (auto e = event.cast<Nova::Event::KeyPress>()) {
		int dir = (Nova::Input::Poll(Nova::Input::Key::LCTRL) || Nova::Input::Poll(Nova::Input::Key::RCTRL)) ? -1 : 1;
		if (e.match(Nova::Input::Key::J)) {
			float upload;
			m_buffer->get("scan_angle", &upload);
			upload += 1.0f * dir;
			m_buffer->set("scan_angle", &upload);
			std::cout << "Angle: " << static_cast<int>(upload) << std::endl;

		} else if (e.match(Nova::Input::Key::K)) {
			float upload;
			m_buffer->get("steering", &upload);
			upload += 0.01f * dir;
			m_buffer->set("steering", &upload);
			std::cout << "Steering: " << upload << std::endl;

		} else if (e.match(Nova::Input::Key::L)) {
			float upload;
			m_buffer->get("scan_dist", &upload);
			upload += 5.0f * dir;
			m_buffer->set("scan_dist", &upload);
			std::cout << "Distance: " << static_cast<int>(upload) << std::endl;

		} else if (e.match(Nova::Input::Key::F)) {
			s_properties.fade += 0.1f * dir;
			m_fade->Upload()->Float("u_fade", s_properties.fade);
			std::cout << "Fade: " << s_properties.fade << std::endl;

		} else if (e.match(Nova::Input::Key::G)) {
			s_properties.diffuse += 1.0f * dir;
			m_fade->Upload()->Float("u_diffuse", s_properties.diffuse);
			std::cout << "Diffuse: " << s_properties.diffuse << std::endl;

		} else if (e.match(Nova::Input::Key::E)) {
			Nova::glm::vec4 upload;
			m_buffer->get("colour", &upload);
			upload.r += 0.05f * dir;
			m_buffer->set("colour", &upload);
			std::cout << "Colour: " << upload.x << ", " << upload.y << ", " << upload.z << std::endl;
		} else if (e.match(Nova::Input::Key::R)) {
			Nova::glm::vec4 upload;
			m_buffer->get("colour", &upload);
			upload.g += 0.05f * dir;
			m_buffer->set("colour", &upload);
			std::cout << "Colour: " << upload.x << ", " << upload.y << ", " << upload.z << std::endl;
		} else if (e.match(Nova::Input::Key::T)) {
			Nova::glm::vec4 upload;
			m_buffer->get("colour", &upload);
			upload.b += 0.05f * dir;
			m_buffer->set("colour", &upload);
			std::cout << "Colour: " << upload.x << ", " << upload.y << ", " << upload.z << std::endl;
		}
	}
}