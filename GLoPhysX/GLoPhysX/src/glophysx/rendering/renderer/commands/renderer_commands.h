#pragma once
/*
* @file render_commands.h
* @brief Declaration of the RendererCommands class
* 
* This class is the "public" interface that is used to call RendererAPI methods.
* It offers platform-independent logic to use the API's functionality.
* 
* @see RendererAPI
* 
* @version 1.0
* @date 27-10-2023
* @author Secareanu Filip
*/

#include "glophysx/rendering/renderer/api/renderer_api.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class RendererCommands
		{
		public:
			GLOP_API static void Init() { s_renderer_api->Init(); }

			GLOP_API static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_renderer_api->SetViewport(x, y, width, height); }
			GLOP_API static void SetClearColor(const glm::vec4& color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)) { s_renderer_api->SetClearColor(color); }
			GLOP_API static void Clear() { s_renderer_api->Clear(); }

			GLOP_API static void DrawIndexed(const Shared<VertexArray>& vertex_array, uint32_t index_count = 0) { s_renderer_api->DrawIndexed(vertex_array, index_count); }

			GLOP_API static void SetApi() { s_renderer_api = RendererAPI::Create(); }

		private:
			static Unique<RendererAPI> s_renderer_api;
		};
	}
}
