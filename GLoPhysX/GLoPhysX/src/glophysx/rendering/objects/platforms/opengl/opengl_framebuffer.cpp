#include "gxpch.h"
#include "opengl_framebuffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		static bool IsDepthFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8:
					{
						return true;
					}
			}

			return false;
		}

		static GLenum OpenglTextureFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
			case FramebufferTextureFormat::None:
				break;
			case FramebufferTextureFormat::RGBA8:
				return GL_RGBA8;
			case FramebufferTextureFormat::RED_INTEGER:
				return GL_RED_INTEGER;
			}

			return 0;
		}

		static GLenum OpenglTextureFormatDataType(FramebufferTextureFormat format)
		{
			switch (format)
			{
			case FramebufferTextureFormat::None:
				break;
			case FramebufferTextureFormat::RGBA8:
				return GL_UNSIGNED_BYTE;
			case FramebufferTextureFormat::RED_INTEGER:
				return GL_INT;
			}

			return 0;
		}

		static GLenum TextureTarget(bool multisample)
		{
			return multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void CreateTextures(bool multisample, GLuint* out_id, GLuint count)
		{
			glCreateTextures(TextureTarget(multisample), count, out_id);
		}

		static void BindTexture(bool multisample, GLuint id)
		{
			glBindTexture(TextureTarget(multisample), id);
		}

		static void AttachColorTexture(GLuint id, int samples, GLenum internal_format, GLenum format, GLuint width, GLuint height, int index)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}

		static void AttachDepthTexture(GLuint id, int samples, GLenum format, GLenum attachment_type, GLuint width, GLuint height)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachment_type, TextureTarget(multisampled), id, 0);
		}

		OpenglFramebuffer::OpenglFramebuffer(const FramebufferSpecs& specs) : m_specs(specs)
		{
			for (auto& format : m_specs.attachments.m_attachments)
			{
				if (!IsDepthFormat(format.m_format))
				{
					m_color_attachment_specs.emplace_back(format);
				}
				else
				{
					m_depth_attachment_spec = format;
				}
			}

			Create();
		}

		OpenglFramebuffer::~OpenglFramebuffer()
		{
			glDeleteFramebuffers(1, &m_id);
			glDeleteTextures(m_color_attachments.size(), m_color_attachments.data());
			glDeleteTextures(1, &m_depth_attachment);
		}

		void OpenglFramebuffer::Create()
		{
			if (m_id) {
				glDeleteFramebuffers(1, &m_id);
				glDeleteTextures(m_color_attachments.size(), m_color_attachments.data());
				glDeleteTextures(1, &m_depth_attachment);

				m_color_attachments.clear();
				m_depth_attachment = 0;
			}

			glCreateFramebuffers(1, &m_id);
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);

			bool multisampled = m_specs.samples > 1;

			// Color Attachment
			if (m_color_attachment_specs.size())
			{
				m_color_attachments.resize(m_color_attachment_specs.size());
				CreateTextures(multisampled, m_color_attachments.data(), m_color_attachments.size());

				for (size_t i = 0; i < m_color_attachment_specs.size(); i++)
				{
					BindTexture(multisampled, m_color_attachments[i]);
					switch (m_color_attachment_specs[i].m_format)
					{
					case FramebufferTextureFormat::RGBA8:
						AttachColorTexture(m_color_attachments[i], m_specs.samples, GL_RGBA8, GL_RGBA, m_specs.width, m_specs.height, i);
						break;
					case FramebufferTextureFormat::RED_INTEGER:
						AttachColorTexture(m_color_attachments[i], m_specs.samples, GL_R32I, GL_RED_INTEGER, m_specs.width, m_specs.height, i);
						break;
					}
				}

			}

			// Depth Attachment
			if (m_depth_attachment_spec.m_format != FramebufferTextureFormat::None)
			{
				CreateTextures(multisampled, &m_depth_attachment, 1);
				BindTexture(multisampled, m_depth_attachment);

				switch (m_depth_attachment_spec.m_format)
				{
				case FramebufferTextureFormat::DEPTH24STENCIL8:
					AttachDepthTexture(m_depth_attachment, m_specs.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_specs.width, m_specs.height);
					break;
				}
			}

			// Draw Buffers
			if (m_color_attachments.size() > 1)
			{
				GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
				glDrawBuffers(m_color_attachments.size(), buffers);
			}
			else if (m_color_attachments.empty())
			{
				glDrawBuffer(GL_NONE);
			}

			// Check
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

		int OpenglFramebuffer::ReadPixel(uint32_t index, int x, int y)
		{
			if (index > m_color_attachments.size()) {
				GLOP_CORE_CRITICAL("Too many color attachments. Maximum is {0}, while there are {1} provided", m_color_attachments.size(), index);
				exit(-1);
			}
			glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
			int pixel_data;
			glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixel_data);

			return pixel_data;
		}

		void OpenglFramebuffer::ClearAttachment(uint32_t index, const void* value)
		{
			if (index > m_color_attachments.size()) {
				GLOP_CORE_CRITICAL("Too many color attachments. Maximum is {0}, while there are {1} provided", m_color_attachments.size(), index);
					exit(-1);
			}

			auto& spec = m_color_attachment_specs[index];

			glClearTexImage(
				m_color_attachments[index],
				0,
				OpenglTextureFormat(spec.m_format),
				OpenglTextureFormatDataType(spec.m_format),
				&value);
		}

		void OpenglFramebuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
			glViewport(0, 0, m_specs.width, m_specs.height);

			ClearAttachment(1, (const void*)(-1));
		}

		void OpenglFramebuffer::Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}
