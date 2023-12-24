#pragma once

#include "glophysx/core/core.h"

namespace GLOPHYSX {

	namespace RENDERING {

		enum class FramebufferTextureFormat
		{
			None,

			// Color
			RGBA8,
			RED_INTEGER,

			// DEPTH
			DEPTH24STENCIL8,

			// Defaults
			Depth = DEPTH24STENCIL8
		};

		struct FramebufferTextureSpec
		{
			FramebufferTextureSpec() = default;
			FramebufferTextureSpec(FramebufferTextureFormat format)
			{
				m_format = format;
			}

			FramebufferTextureFormat m_format = FramebufferTextureFormat::None;
		};

		struct FramebufferAttachmentSpec
		{
			FramebufferAttachmentSpec() = default;
			FramebufferAttachmentSpec(std::initializer_list<FramebufferTextureSpec> attachments)
				: m_attachments(attachments) {}


			std::vector<FramebufferTextureSpec> m_attachments;
		};

		struct FramebufferSpecs
		{
			uint32_t width;
			uint32_t height;

			FramebufferAttachmentSpec attachments;

			uint32_t samples = 1;
			bool swapchain_target = false;
		};

		class Framebuffer
		{
		public:
			virtual ~Framebuffer() = default;

			virtual void Resize(uint32_t width, uint32_t height) = 0;
			virtual int ReadPixel(uint32_t index, int x, int y) = 0;
			virtual void ClearAttachment(uint32_t index, const void* value) = 0;

			virtual FramebufferSpecs& GetSpecs() = 0;
			virtual const FramebufferSpecs& GetSpecs() const = 0;

			virtual uint32_t GetColorAttachmentId(uint32_t index = 0) const = 0;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			static Shared<Framebuffer> Create(const FramebufferSpecs& specs);
		};
	}
}
