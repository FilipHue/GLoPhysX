#include "gxpch.h"
#include "graphics_context.h"
#include "glophysx/renderer/context/platforms/opengl/opengl_context.h"
#include "glophysx/renderer/renderer/api/renderer_api.h"

namespace GLOPHYSX {

	namespace RENDERER {

		Unique<GraphicsContext> GraphicsContext::Create(void* window)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return MakeUnique<OpenglContext>(static_cast<GLFWwindow*>(window));
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
