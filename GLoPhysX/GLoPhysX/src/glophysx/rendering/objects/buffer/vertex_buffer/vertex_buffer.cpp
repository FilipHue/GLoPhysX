#include "gxpch.h"
#include "vertex_buffer.h"

#include "glophysx/rendering/renderer/api/renderer_api.h"
#include "glophysx/rendering/objects/buffer/platforms/opengl/opengl_vertex_buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		GLOP_API Shared<VertexBuffer> VertexBuffer::Create(uint32_t size)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return MakeShared<OpenglVertexBuffer>(size);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}

		Shared<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return MakeShared<OpenglVertexBuffer>(vertices, size);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
