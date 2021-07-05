#pragma once
#include "spch.h"
#include <nova.h>

class Ants {
public:
	Ants(const unsigned int blocks, const unsigned int width, const unsigned int height);

	void update();

	void event(Nova::Event::Event& event);

	const Nova::Star<Nova::Texture2D>& get_texture() const { return m_texture; }
protected:
	Nova::Star<Nova::Texture2D> m_texture;
	Nova::Star<Nova::ShaderCompute> m_agent, m_fade;
	Nova::Star<Nova::Buffer::Shader> m_buffer;

	struct Agent {
		Nova::glm::vec2 pos{ 0.0 }, vel{ 0.0 }; // , acc{ 0.0 };
	};
};