#pragma once
/**
* @file wwindow.h
* @brief Header file for the WWindow class, a concrete implementation of the Window class for Windows system.
*
* This file defines the WWindow class, a specific implementation of the Window abstract class tailored for
* the GLFW windowing system. The WWindow class provides functionalities to create, manage, and destroy windows,
* as well as handle window-related events in a GLFW context.
*
* The class is designed to be used within the GLoPhysX engine to abstract away the complexities of window management
* and provide a uniform interface for window operations, irrespective of the underlying windowing system.
*
* @see Window
* @see WindowProperties
* @see GraphicContext
* 
* @version 1.0
* @date 2023-10-27
* @author Secareanu Filip
*/

/*
* The inclusion order of headers is crucial to prevent compilation issues and warnings.
* core.h includes windows.h, which defines various macros, including APIENTRY.
* However, glad.h, responsible for providing OpenGL function pointers, explicitly
* undefines the APIENTRY macro to ensure proper compilation across different platforms
* and environments.
*
* To avoid any potential warnings or redefinition issues due to this macro manipulation,
* it is necessary to include core.h before glad.h. This ensures that windows.h is processed
* first, followed by the adjustments made by glad.h, maintaining a clean and warning-free
* compilation process.
*/
#include "glophysx/core/core.h"

/*
* It is crucial to include glad.h before glfw3.h because glad provides the necessary
* function pointers for interacting with OpenGL functions. The inclusion order ensures
* that these function pointers are available and properly configured before any other
* headers attempt to use OpenGL functions.
*
* glfw3.h may implicitly include some default OpenGL headers. If glad.h were included after
* glfw3.h, these default headers would be processed before glad has had an opportunity to
* declare the OpenGL function pointers, potentially leading to compilation errors and conflicts.
* This is because the default headers might declare OpenGL functions that conflict with the
* function pointers provided by glad.
*
* By including glad.h first, we ensure that the OpenGL function pointers are correctly set up
* before any other headers attempt to use or declare OpenGL functions, maintaining proper
* function resolution and avoiding compilation issues.
*/
#include "glad/glad.h"
#include "glfw3.h"

#include "glophysx/core/window/window.h"

#include "glophysx/core/events/application_events.h"
#include "glophysx/core/events/key_events.h"
#include "glophysx/core/events/mouse_events.h"

#include "glophysx/renderer/context/graphics_context.h"

namespace GLOPHYSX {

	using namespace RENDERER;

	/**
	* @struct WindowData
	* @brief Holds state and contextual information for a window instance.
	*
	* The WindowData structure is designed to encapsulate all relevant data pertaining to
	* a specific window. This includes the window's position, its set of properties (such as
	* size, title, and other attributes defined in WindowProperties), and the event callback
	* function. By bundling this data into a single structure, we provide a clean way to
	* manage window state and pass it around the system as needed.
	*
	* This structuring is particularly useful for callback functions where user pointer
	* tricks are often used to pass window context information to event handlers. Instead of
	* using multiple disparate variables, a single WindowData instance can be passed, thereby
	* reducing the complexity of the code and improving maintainability.
	*
	* In the context of GLFW, which allows setting a user pointer on each window, the
	* WindowData structure can be directly associated with a GLFWwindow. This means that any
	* GLFW callback can retrieve a window's contextual data through the GLFWwindow user pointer,
	* facilitating access to custom GLoPhysX engine data and callbacks from within the GLFW callback
	* functions.
	*/
	typedef struct window_data WindowData;
	struct window_data {
		unsigned int x_pos, y_pos;

		WindowProperties* wp;
		Window::EventCallbackFn event_callback;
	};

	/**
	* @class WWindow
	* @brief Concrete implementation of the Window class for the Windows system.
	*
	* WWindow encapsulates the creation, management, and destruction of windows
	* using GLFW. It provides the necessary interfaces to handle window events
	* and integrates seamlessly with the GLoPhysX engine’s event system.
	*/
	class WWindow : public Window
	{
	public:
		GLOP_API WWindow(WindowProperties* wp);
		GLOP_API ~WWindow();

		GLOP_API void Initialize(WindowProperties* wp) override;
		GLOP_API void Update() override;
		GLOP_API void Destroy() override;

		GLOP_API void SetEventCallback(const EventCallbackFn& callback) override;

		GLOP_API void* GetNativeWindow() const override;

	private:
		void SetWindowCallbacks() override;
		void SetMouseCallbacks() override;
		void SetKeyCallbacks() override;

	private:
		GLFWmonitor* m_monitor;
		GLFWwindow* m_window;
		std::unique_ptr<GraphicsContext> m_contex;

		const GLFWvidmode* m_video_mode;

		WindowData m_window_data;
	};
}
