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
#include "glophysx/renderer/camera/camera.h"	

namespace GLOPHYSX {

	namespace RENDERER {

		class Renderer
		{
		public:
			GLOP_API static void Init();
			GLOP_API static void ShutDown();

			GLOP_API static void OnWindowResize(uint32_t width, uint32_t height);

			GLOP_API static void BeginScene(const Shared<Camera> camera);
			GLOP_API static void EndScene();

			GLOP_API static void Submit(const Shared<Shader> shader, const Shared<VertexArray>& vertex_array, const glm::mat4 model_matrix, uint32_t index_count = 0);

			GLOP_API static API GetApi() { return RendererAPI::GetApi(); }

		private:
			static glm::mat4 m_vp_scene_matrix;
		};
	}
}
