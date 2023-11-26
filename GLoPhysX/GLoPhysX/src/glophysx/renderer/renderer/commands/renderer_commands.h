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

#include "glophysx/renderer/renderer/api/renderer_api.h"

namespace GLOPHYSX {

	namespace RENDERER {

		class RendererCommands
		{
		public:
			static void Init() { s_renderer_api->Init(); }

			static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_renderer_api->SetViewport(x, y, width, height); }
			static void SetClearColor(const glm::vec4& color = glm::vec4(1.f, 0.f, 1.f, 1.f)) { s_renderer_api->SetClearColor(color); }
			static void Clear() { s_renderer_api->Clear(); }

			static void DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array, uint32_t index_count = 0) { s_renderer_api->DrawIndexed(vertex_array, index_count); }

			GLOP_API static void SetApi() { s_renderer_api = RendererAPI::Create(); }

		private:
			static std::unique_ptr<RendererAPI> s_renderer_api;
		};
	}
}
