#pragma once
/*
* @file opengl_renderer_api.h
* @brief Declaration of the OpenGL rendering API class
* 
* This header file contains the platfrom-specific implementation of the GLoPhysX
* renderer engine, for OpenGL
* 
* @see RendererAPI
* 
* @version 1.0
* @date 27-10-2023
* @author Secareanu Filip
*/

#include "glophysx/core/core.h"
#include "glophysx/rendering/renderer/api/renderer_api.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class OpenglRendererAPI : public RendererAPI
		{
			virtual void Init() override;

			virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
			virtual void SetClearColor(const glm::vec4& color) override;
			virtual void Clear() override;

			virtual void DrawIndexed(const Shared<VertexArray>& vertex_array, uint32_t index_count = 0) override;
		};
	}
}
