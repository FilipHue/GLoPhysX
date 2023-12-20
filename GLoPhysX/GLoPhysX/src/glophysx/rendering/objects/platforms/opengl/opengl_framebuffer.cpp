#include "gxpch.h"
#include "opengl_framebuffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		OpenglFramebuffer::OpenglFramebuffer(const FramebufferSpecs& specs) : m_specs(specs)
		{
			Create();
		}

		OpenglFramebuffer::~OpenglFramebuffer()
		{
			glDeleteFramebuffers(1, &m_id);
			glDeleteTextures(1, &m_color_attachment);
			glDeleteTextures(1, &m_depth_attachment);
		}

		void OpenglFramebuffer::Create()
		{
			if (m_id) {
				glDeleteFramebuffers(1, &m_id);
				glDeleteTextures(1, &m_color_attachment);
				glDeleteTextures(1, &m_depth_attachment);
			}

			glCreateFramebuffers(1, &m_id);
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);

			glCreateTextures(GL_TEXTURE_2D, 1, &m_color_attachment);
			glBindTexture(GL_TEXTURE_2D, m_color_attachment);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_specs.width, m_specs.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_attachment, 0);

			glCreateTextures(GL_TEXTURE_2D, 1, &m_depth_attachment);
			glBindTexture(GL_TEXTURE_2D, m_depth_attachment);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_specs.width, m_specs.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_attachment, 0);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				GLOP_CORE_CRITICAL("Framebuffer was not succesfully created");
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void OpenglFramebuffer::Resize(uint32_t width, uint32_t height)
		{
			m_specs.width = width;
			m_specs.height = height;

			Create();
		}

		void OpenglFramebuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
			glViewport(0, 0, m_specs.width, m_specs.height);
		}

		void OpenglFramebuffer::Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}
