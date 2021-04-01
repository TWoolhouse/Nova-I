#include "npch.h"
#include "render.h"
#include "command.h"

struct RenderState {
	//framebuffer;
};

static RenderState* render_state = nullptr;

namespace Nova {

	bool Render::Initialise() {
		render_state = new RenderState();
		return Render::Command::Initialise();
	}

	bool Render::Termintate() {
		return Render::Command::Termintate();
		delete render_state;
	}

	void Render::Scene() {
		
	}

	void Render::Draw(Buffer::Context* context, Shader* shader) {
		shader->bind();
		Render::Command::Draw(context);
	}

}