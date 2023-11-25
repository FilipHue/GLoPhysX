#include "gxpch.h"
#include "vertex_array.h"

#include "glophysx/renderer/primitives/platforms/opengl/opengl_vertex_array.h"
#include "glophysx/renderer/renderer/renderer_api.h"

namespace GLOPHYSX {

	namespace RENDERER {
		std::shared_ptr<VertexArray> VertexArray::Create()
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return std::make_shared<OpenglVertexArray>();
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
