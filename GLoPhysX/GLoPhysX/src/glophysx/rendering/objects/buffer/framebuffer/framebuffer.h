#pragma once

#include "glophysx/core/core.h"

#include "framebuffer_utils.h"

namespace GLOPHYSX {

	namespace RENDERING {

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
			virtual void Unbind() const = 0;

			static Shared<Framebuffer> Create(const FramebufferSpecs& specs);
		};
	}
}
