#include "gxpch.h"
#include "shader.h"

#include "glophysx/renderer/renderer/api/renderer_api.h"
#include "glophysx/renderer/shader/platforms/opengl/opengl_shader.h"

namespace GLOPHYSX {

	namespace RENDERER {

		std::shared_ptr<Shader> Shader::Create(std::string& source_vs, std::string& source_fs)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API")
				return nullptr;
			case API::OPENGL:
				return std::make_shared<OpenglShader>(source_vs, source_fs);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API")
				return nullptr;
		}
	}
}
