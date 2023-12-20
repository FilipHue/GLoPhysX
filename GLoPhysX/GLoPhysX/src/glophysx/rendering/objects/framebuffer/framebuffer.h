#pragma once

#include "glophysx/core/core.h"

namespace GLOPHYSX {

	namespace RENDERING {

		struct FramebufferSpecs
		{
			uint32_t width;
			uint32_t height;

			bool swapchain_target = false;
		};

		class Framebuffer
		{
		public:
			virtual ~Framebuffer() = default;

			virtual FramebufferSpecs& GetSpecs() = 0;
			virtual const FramebufferSpecs& GetSpecs() const = 0;

			virtual uint32_t GetColorAttachmentId() const = 0;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			static Shared<Framebuffer> Create(const FramebufferSpecs& specs);
		};
	}
}
