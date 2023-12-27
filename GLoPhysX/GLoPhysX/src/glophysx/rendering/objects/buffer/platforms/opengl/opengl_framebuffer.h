#pragma once

#include "glophysx/rendering/objects/buffer/framebuffer/framebuffer.h"

#include "glad/glad.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class OpenglFramebuffer : public Framebuffer
		{
		public:
			OpenglFramebuffer(const FramebufferSpecs& specs);
			virtual ~OpenglFramebuffer();

			void Create();
			void Resize(uint32_t width, uint32_t height) override;
			int ReadPixel(uint32_t index, int x, int y) override;
			void ClearAttachment(uint32_t index, const void* value) override;

			FramebufferSpecs& GetSpecs() override { return m_specs; }
			const FramebufferSpecs& GetSpecs() const override { return m_specs; }

			uint32_t GetColorAttachmentId(uint32_t index = 0) const { return m_color_attachments[index]; }

			void Bind() override;
			void Unbind() override;
			 
		private:
			uint32_t m_id = 0;

			std::vector<uint32_t> m_color_attachments;
			uint32_t m_depth_attachment = 0;

			FramebufferSpecs m_specs;

			std::vector<FramebufferTextureSpec> m_color_attachment_specs;
			FramebufferTextureSpec m_depth_attachment_spec = FramebufferTextureFormat::None;
		};
	}
}
