#include "gxpch.h"
#include "framebuffer.h"

#include "glophysx/rendering/renderer/api/renderer_api.h"
#include "glophysx/rendering/objects/buffer/platforms/opengl/opengl_framebuffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		Shared<Framebuffer> Framebuffer::Create(const FramebufferSpecs& specs)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return MakeShared<OpenglFramebuffer>(specs);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
