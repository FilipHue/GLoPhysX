#pragma once
/*
* @file renderer_api.h
* @brief Declaration of the RendererAPI class
* 
* This header file defines the RendererAPI class, which represents an abstraction for the
* rendering API of the GLoPhysX renderer. It provides the means to set and get the renderere API
* used by the system (OpenGL, Vulkan, DirectX3D etc.), as well as an interface for basic
* functionalities like setting the viewport, clearing the screen and drawing.
* This file must be subclassed to provide paltform-specific functionality.
* 
* @version 1.0
* @date 27-10-2023
* @author Secareanu Filip
*/

#include "glophysx/core/core.h"

#include "glophysx/rendering/objects/vertex_array.h"

#include "glm.hpp"

namespace GLOPHYSX {
	
	namespace RENDERING {

		// The rendering API types that are suppported
		enum class API {
			NONE,
			OPENGL
		};

		class RendererAPI {
		public:
			virtual ~RendererAPI() = default;

			// Method can be called at the initialization of the engine and can be used to call platform-specific functions.
			virtual void Init() = 0;

			virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
			virtual void SetClearColor(const glm::vec4& color) = 0;
			virtual void Clear() = 0;

			// Method used to draw vertices on the screen using and index buffer
			virtual void DrawIndexed(const Shared<VertexArray>& vertex_array, uint32_t index_count = 0) = 0;

			GLOP_API static API GetApi() { return s_API; }
			GLOP_API static void SetApi(API graphics_api) { s_API = graphics_api; }

			static Unique<RendererAPI> Create();

		private:
			static API s_API;
		};
	}
}
