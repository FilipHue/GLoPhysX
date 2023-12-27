#include "gxpch.h"
#include "uniform_buffer.h"

#include "glophysx/rendering/renderer/api/renderer_api.h"
#include "glophysx/rendering/objects/buffer/platforms/opengl/opengl_uniform_buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		Shared<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return MakeShared<OpenglUniformBuffer>(size, binding);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
