#include "gxpch.h"
#include "buffer.h"
#include "glophysx/renderer/primitives/platforms/opengl/opengl_buffer.h"

#include "glophysx/renderer/renderer/renderer_api.h"

namespace GLOPHYSX {

	namespace RENDERER {

		std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return std::make_shared<OpenglVertexBuffer>(vertices, size);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
		std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* vertices, uint32_t size)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return std::make_shared<OpenglIndexBuffer>(vertices, size);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
