#include "gxpch.h"
#include "buffer.h"
#include "glophysx/rendering/objects/platforms/opengl/opengl_buffer.h"

#include "glophysx/rendering/renderer/api/renderer_api.h"

namespace GLOPHYSX {

	namespace RENDERING {

		GLOP_API std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return std::make_shared<OpenglVertexBuffer>(size);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}

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
