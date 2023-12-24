#include "gxpch.h"
#include "renderer_api.h"

#include "platforms/opengl/opengl_renderer_api.h"

namespace GLOPHYSX {

	namespace RENDERING {

		API RendererAPI::s_API = API::NONE;
		Unique<RendererAPI> RendererAPI::Create()
		{
			switch (s_API)
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return MakeUnique<OpenglRendererAPI>();
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
