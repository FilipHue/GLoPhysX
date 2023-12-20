#pragma once

#include "glophysx/rendering/objects/framebuffer/framebuffer.h"

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

			FramebufferSpecs& GetSpecs() override { return m_specs; }
			const FramebufferSpecs& GetSpecs() const override { return m_specs; }

			uint32_t GetColorAttachmentId() const { return m_color_attachment; }

			void Bind() override;
			void Unbind() override;
			 
		private:
			uint32_t m_id = 0;

			uint32_t m_color_attachment = 0;
			uint32_t m_depth_attachment = 0;

			FramebufferSpecs m_specs;
		};
	}
}
