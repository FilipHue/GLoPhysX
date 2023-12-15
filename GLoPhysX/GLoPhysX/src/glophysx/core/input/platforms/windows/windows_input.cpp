#include "gxpch.h"
#include "windows_input.h"

#include "glophysx/core/application/application.h"

namespace GLOPHYSX {

	bool WindowsInput::PIsKeyPressed(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS;
	}

	bool WindowsInput::PIsKeyRepeated(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);

		return state == GLFW_REPEAT;
	}

	bool WindowsInput::PIsMouseButtonPressed(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	double WindowsInput::PGetMouseX()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());

		double x_pos, y_pos;

		glfwGetCursorPos(window, &x_pos, &y_pos);

		return x_pos;
	}

	double WindowsInput::PGetMouseY()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());

		double x_pos, y_pos;

		glfwGetCursorPos(window, &x_pos, &y_pos);

		return y_pos;
	}
}
