#include "npch.h"

#ifdef NOVA_OPENGL
#include <GL/glew.h>
#include "render/command.h"
#include "render/draw/draw_quad.h"

namespace Nova {

	void Nova::RenderDraw::Quad::Flush() {
		const auto& buff = batch->data();

		batch->vertex().set(buff, batch->count() * sizeof(Block), 0);

		shader->bind();
		batch->context().bind();
		textures.bind();
		Render::Command::DrawPoint(&batch->context(), batch->count());
		batch->reset();
	}

}

#endif // NOVA_OPENGL