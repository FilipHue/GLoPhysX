#include "gxpch.h"
#include "wwindow.h"

namespace GLOPHYSX {

	static uint8_t s_window_count = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		GLOP_CORE_ERROR("GLFW error {0}: {1}", error, description);
	}

	WWindow::WWindow(WindowProperties* wp)
	{
		Initialize(wp);
	}

	WWindow::~WWindow()
	{
		GLOP_CORE_INFO("Destroying window...");
		Destroy();
	}

	void WWindow::Initialize(WindowProperties* wp)
	{
		int succesful_init = glfwInit();
		if (succesful_init) {
			GLOP_CORE_INFO("Succesfully initialized glfw library");
			glfwSetErrorCallback(GLFWErrorCallback);
		}
		else {
			GLOP_CORE_ERROR("Failed to initialize glfw library");
			return;
		}

		GLOP_CORE_INFO("Creating Windows window {0}: {1} by {2}", wp->title, wp->width, wp->height);

		properties = wp;
		m_window_data.wp = properties;
		s_window_count++;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_monitor = glfwGetPrimaryMonitor();
		m_video_mode = glfwGetVideoMode(m_monitor);
		m_window = glfwCreateWindow(properties->width, properties->height, properties->title, NULL, NULL);
		if (m_window == nullptr) {
			GLOP_CORE_ERROR("Failed to create a window. Terminating library...");
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			GLOP_CORE_ERROR("GLAD not initialized");
		}

		GLOP_CORE_INFO("Window succesfully created");

		glfwSetWindowUserPointer(m_window, &m_window_data);
		
		GLOP_CORE_INFO("Setting window callbacks");

		SetCallbacks();
	}

	void WWindow::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WWindow::Destroy()
	{
		glfwDestroyWindow(m_window);
		s_window_count--;

		if (s_window_count == 0) {
			glfwTerminate();
		}
	}

	void WWindow::SetEventCallback(const EventCallbackFn& callback)
	{
		m_window_data.event_callback = callback;
	}

	void* WWindow::GetWindow() const
	{
		return m_window;
	}
	void WWindow::SetWindowCallbacks()
	{
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window_handle) {
			WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window_handle);
			WindowCloseEvent event;

			window_data.event_callback(event);
			});

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window_handle, int width, int height) {
			WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window_handle);
			WindowResizeEvent event(width, height);

			window_data.wp->width = width;
			window_data.wp->height = height;
			window_data.wp->aspect_ration = (float)width / height;

			window_data.event_callback(event);
			});

		glfwSetWindowPosCallback(m_window, [](GLFWwindow* window_handle, int x, int y) {
			WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window_handle);

			WindowMoveEvent event(x, y);

			window_data.x_pos = x;
			window_data.y_pos = y;

			window_data.event_callback(event);
			});

		glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window_handle, int focus) {
			WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window_handle);

			WindowFocusEvent event(focus);

			window_data.event_callback(event);
			});

		glfwSetWindowIconifyCallback(m_window, [](GLFWwindow* window_handle, int iconify) {
			WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window_handle);

			WindowIconifyEvent event(iconify);

			window_data.event_callback(event);
			});
	}
	void WWindow::SetMouseCallbacks()
	{
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window_handle, int button, int action, int mods) {
			WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window_handle);

			switch (action)
			{
			case GLFW_PRESS:
			{MouseButtonPressEvent event(button, mods);

			window_data.event_callback(event);
			break;
			}
			case GLFW_RELEASE:
			{MouseButtonReleaseEvent event(button, mods);

			window_data.event_callback(event);
			break;
			}
			default:
				break;
			}
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window_handle, double x_pos, double y_pos) {
			WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window_handle);

			MouseMoveEvent event(x_pos, y_pos);

			window_data.event_callback(event);
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window_handle, double x_offset, double y_offset) {
			WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window_handle);

			MouseScrollEvent event(x_offset, y_offset);

			window_data.event_callback(event);
			});
	}
	void WWindow::SetKeyCallbacks()
	{
		glfwSetKeyCallback(m_window, [](GLFWwindow* window_handle, int key, int scancode, int action, int mods) {
			WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window_handle);

			switch (action)
			{
			case GLFW_PRESS:
			{KeyPressEvent event(key, mods, 0);

			window_data.event_callback(event);
			break;
			}
			case GLFW_RELEASE:
			{KeyReleaseEvent event(key, mods);

			window_data.event_callback(event);
			break;
			}
			case GLFW_REPEAT:
			{KeyPressEvent event(key, mods, 1);

			window_data.event_callback(event);
			break;
			}
			default:
				break;
			}
			});

		glfwSetCharCallback(m_window, [](GLFWwindow* window_handle, unsigned int codepoint) {
			WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window_handle);

			KeyTypedEvent event(codepoint);

			window_data.event_callback(event);
			});
	}
}
