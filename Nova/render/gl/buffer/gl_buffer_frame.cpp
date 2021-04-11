#include "npch.h"

#ifdef NOVA_OPENGL
#include "render/gl/gl_bind_helper.h"
#include <GL/glew.h>
#include "gl_buffer_frame.h"
#include "render/gl/gl_texture.h"

namespace Nova {

	Buffer::Frame* Buffer::Frame::Create() {
		return new OpenGL::BufferFrame();
	}

	namespace OpenGL {

		BufferFrame::BufferFrame() : m_id(GL_NONE) {
			glCreateFramebuffers(1, &m_id);
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		}

		BufferFrame::~BufferFrame() {
			glDeleteFramebuffers(1, &m_id);
		}

		void BufferFrame::bind() {
			#ifndef NDEBUG
			if (!m_success) throw std::runtime_error("FrameBuffer Not Complete");
			#endif
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		}

		void BufferFrame::unbind() {
			glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
		}

		void BufferFrame::attach_colour(Nova::Texture2D* texture) {
			nova_gl_bind(GL_DRAW_FRAMEBUFFER_BINDING, m_id);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, static_cast<OpenGL::Texture2D*>(texture)->m_id, 0);
		}
		void BufferFrame::attach_depth_stencil(Nova::Texture2D* texture) {
			nova_gl_bind(GL_DRAW_FRAMEBUFFER_BINDING, m_id);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, static_cast<OpenGL::Texture2D*>(texture)->m_id, 0);
		}

		const bool BufferFrame::validate() {
			nova_gl_bind(GL_DRAW_FRAMEBUFFER_BINDING, m_id);
			m_success = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
			if (!m_success) glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
			return m_success;
		}

	}

}

#endif // NOVA_OPENGL
