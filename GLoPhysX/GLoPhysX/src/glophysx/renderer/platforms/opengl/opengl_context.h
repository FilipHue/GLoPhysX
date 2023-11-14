#pragma once

#include "glophysx/renderer/graphics_context.h"
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
