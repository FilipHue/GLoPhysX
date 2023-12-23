#include "gxpch.h"
#include "texture.h"

#include "glophysx/rendering/renderer/api/renderer_api.h"

#include "glophysx/rendering/objects/texture/platforms/opengl/opengl_texture_2D.h"

namespace GLOPHYSX {

	namespace RENDERING {

		Shared<Texture2D> Texture2D::Create(const std::string& path, int flip, uint32_t x_offset, uint32_t y_offset)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return MakeShared<OpenglTexture2D>(path, flip, x_offset, y_offset);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}

		Shared<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
		{
			switch (RendererAPI::GetApi())
			{
			case API::NONE:
				GLOP_CORE_CRITICAL("Please specify a rendering API");
				return nullptr;
			case API::OPENGL:
				return MakeShared<OpenglTexture2D>(width, height);
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown rendering API");
			return nullptr;
		}
	}
}
