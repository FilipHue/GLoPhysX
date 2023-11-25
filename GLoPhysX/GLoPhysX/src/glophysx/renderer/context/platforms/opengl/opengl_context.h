#pragma once
/**
* @class OpenglContext
* @brief OpenGL graphics context implementation for GLoPhysX.
*
* OpenglContext is responsible for managing the OpenGL rendering context associated with a GLFW window.
* It inherits from the GraphicsContext interface, providing the necessary functionality to initialize,
* present frames, and clean up the OpenGL context.
*
* @see GrahicsContext
* @version 1.0
* @date 2023-10-27
* @author Secareanu Filip
*/

#include "glophysx/renderer/context/graphics_context.h"
#include "glophysx/core/core.h"

#include "glad/glad.h"
#include "glfw3.h"

struct GLFWwindow;

namespace GLOPHYSX {

	namespace RENDERER {

		class OpenglContext : public GraphicsContext
		{
		public:
			OpenglContext(GLFWwindow* window);

			virtual void Init() override;
			virtual void SwapBuffers() override;
			virtual void Destroy() override {};

		private:
			GLFWwindow* m_window_handle;
		};
	}
}
