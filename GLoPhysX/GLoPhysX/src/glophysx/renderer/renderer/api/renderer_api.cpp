#include "gxpch.h"
#include "renderer_api.h"

#include "glophysx/renderer/renderer/api/platforms/opengl/opengl_renderer_api.h"

namespace GLOPHYSX {

	namespace RENDERER {

		API RendererAPI::s_API = API::NONE;
		std::unique_ptr<RendererAPI> RendererAPI::Create()
		{
			switch (s_API)
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API")
				return nullptr;
			case API::OPENGL:
				return std::make_unique<OpenglRendererAPI>();
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API")
			return nullptr;
		}
	}
}
