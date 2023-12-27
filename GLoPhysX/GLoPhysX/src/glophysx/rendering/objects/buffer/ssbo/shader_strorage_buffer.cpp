#include "gxpch.h"
#include "shader_strorage_buffer.h"

#include "glophysx/rendering/renderer/api/renderer_api.h"
#include "glophysx/rendering/objects/buffer/platforms/opengl/opengl_shader_storage_buffer.h"

namespace GLOPHYSX {

	namespace RENDERING {

		Shared<ShaderStorageBuffer> ShaderStorageBuffer::Create(uint32_t size, uint32_t binding)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return MakeShared<OpenglShaderStorageBuffer>(size, binding);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
