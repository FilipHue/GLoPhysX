#include "gxpch.h"
#include "opengl_context.h"

namespace GLOPHYSX {

	namespace RENDERING {
		OpenglContext::OpenglContext(GLFWwindow* window) : m_window_handle(window)
		{
		}
		void OpenglContext::Init()
		{
			GLOP_CORE_INFO("Intializing OpenGL context:");

			glfwMakeContextCurrent(m_window_handle);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				GLOP_CORE_ERROR("GLAD not initialized");
			}

			GLOP_CORE_INFO("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));
			GLOP_CORE_INFO("	RENDERING: {0}", (const char*)glGetString(GL_RENDERER));
			GLOP_CORE_INFO("	Version: {0}", (const char*)glGetString(GL_VERSION));
		}
		void OpenglContext::SwapBuffers()
		{
			glfwSwapBuffers(m_window_handle);
		}
	}
}
