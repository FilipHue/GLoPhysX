#include "gxpch.h"
#include "vertex_array.h"

#include "glophysx/renderer/objects/platforms/opengl/opengl_vertex_array.h"
#include "glophysx/renderer/renderer/api/renderer_api.h"

namespace GLOPHYSX {

	namespace RENDERER {
		Shared<VertexArray> VertexArray::Create()
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return MakeShared<OpenglVertexArray>();
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
