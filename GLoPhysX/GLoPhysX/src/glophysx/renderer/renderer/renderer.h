#pragma once
/*
* @file renderer.h
* @brief Delcaration of the GLoPhysX renderer
* 
* This file contains the logic and implementation of the GLoPhysX renderer.
* It handles the intialization and shuttingdown of the render engine,
* submitting data to be rendered and calls for begining and ending of a scene.
* 
* It also contains other utility function, like OnWindowResize (more can be added, if needed).
* It provides an "abstract" interface for such methods, making the renderig flow much easier
* to understand.
* 
* @see RendererAPI
* @see RendererCommands
* 
* @version 1.0
* @date 27-10-2023
* @author Secareanu Filip
*/

#include "glophysx/core/core.h"
#include "glophysx/renderer/renderer/commands/renderer_commands.h"
#include "glophysx/renderer/shader/shader.h"

namespace GLOPHYSX {

	namespace RENDERER {

		class Renderer
		{
		public:
			static void Init();
			static void ShutDown();

			static void OnWindowResize(uint32_t width, uint32_t height);

			static void BeginScene();
			static void EndScene();

			static void Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertex_array, uint32_t index_count = 0);

			static API GetApi() { return RendererAPI::GetApi(); }
		};
	}
}
