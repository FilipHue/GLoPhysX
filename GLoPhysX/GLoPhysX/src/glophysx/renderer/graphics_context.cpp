#include "gxpch.h"
#include "graphics_context.h"
#include "glophysx/renderer/platforms/opengl/opengl_context.h"
#include "renderer.h"

namespace GLOPHYSX {

	namespace RENDERER {

		std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return std::make_unique<OpenglContext>(static_cast<GLFWwindow*>(window));
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
