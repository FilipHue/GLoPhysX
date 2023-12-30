#include "gxpch.h"
#include "index_buffer.h"

#include "glophysx/rendering/renderer/api/renderer_api.h"
#include "glophysx/rendering/objects/buffer/platforms/opengl/opengl_index_buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		Shared<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return MakeShared<OpenglIndexBuffer>(indices, size);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
