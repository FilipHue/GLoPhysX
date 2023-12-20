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

			FramebufferSpecs& GetSpecs() override { return m_specs; }
			const FramebufferSpecs& GetSpecs() const override { return m_specs; }

			uint32_t GetColorAttachmentId() const { return m_color_attachment; }

			void Bind() override;
			void Unbind() override;
			 
		private:
			uint32_t m_id;

			uint32_t m_color_attachment;
			uint32_t m_depth_attachment;

			FramebufferSpecs m_specs;
		};
	}
}
