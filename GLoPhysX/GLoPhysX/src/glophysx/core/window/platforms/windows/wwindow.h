/**
* @file wwindow.h
* @brief Header file for the WWindow class, a concrete implementation of the Window class for GLFW windowing system.
*
* This file defines the WWindow class, a specific implementation of the Window abstract class tailored for
* the GLFW windowing system. The WWindow class provides functionalities to create, manage, and destroy windows,
* as well as handle window-related events in a GLFW context.
*
* The class is designed to be used within the GLoPhysX engine to abstract away the complexities of window management
* and provide a uniform interface for window operations, irrespective of the underlying windowing system.
*
* The inclusion order of headers in this file is crucial to avoid compilation issues and warnings. This is due
* to the interactions between the windows.h, glad.h, and glfw3.h headers. The core.h header includes windows.h,
* while glad.h explicitly undefines the APIENTRY macro defined by windows.h. To prevent redefinition issues and
* maintain a clean compilation process, core.h must be included before glad.h and glfw3.h. Additionally, glad.h
* must be included before glfw3.h to ensure that the OpenGL function pointers provided by glad are available
* and correctly configured before any GLFW headers that may use these functions.
*
* @see Window
* @see WindowProperties
*
* @version 1.0
* @date 2023-10-27
*/

#pragma once

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

#include "glophysx/events/application_events.h"
#include "glophysx/events/key_events.h"
#include "glophysx/events/mouse_events.h"

namespace GLOPHYSX {

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
	*
	*/
	typedef struct window_data WindowData;
	struct window_data {
		unsigned int x_pos, y_pos;

		WindowProperties* wp;
		Window::EventCallbackFn event_callback;
	};

	/**
	* @class WWindow
	* @brief Concrete implementation of the Window class for the GLFW windowing system.
	*
	* WWindow encapsulates the creation, management, and destruction of windows
	* using GLFW. It provides the necessary interfaces to handle window events
	* and integrates seamlessly with the GLoPhysX engine’s event system.
	*/
	class GLOP_API WWindow : public Window
	{
	public:
		WWindow(WindowProperties* wp);
		~WWindow();

		void Initialize(WindowProperties* wp) override;
		void Update() override;
		void Destroy() override;

		void SetEventCallback(const EventCallbackFn& callback) override;

		void* GetWindow() const override;

	private:
		void SetWindowCallbacks() override;
		void SetMouseCallbacks() override;
		void SetKeyCallbacks() override;

	private:
		GLFWmonitor* m_monitor;
		GLFWwindow* m_window;

		const GLFWvidmode* m_video_mode;

		WindowData m_window_data;
	};
}


