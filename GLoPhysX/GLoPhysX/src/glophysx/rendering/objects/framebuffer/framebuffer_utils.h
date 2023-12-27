#pragma once

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
	}
}
