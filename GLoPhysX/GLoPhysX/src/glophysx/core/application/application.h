#pragma once
/**
* @file application.h
* @brief This file contains the declaration of the Application class and the CreateApplication function.
*
* The Application class represents the core of the GLoPhysX engine. It provides
* the necessary functionality to initialize, run, and shut down the engine. This
* class is intended to be subclassed by the client application to provide
* custom behavior.
* 
* Exporting functions and members selectively is crucial for maintaining a stable
* and error-free interface, especially when dealing with STL templates. STL
* implementations can vary, and exporting them directly might lead to issues and
* warnings due to possible inconsistencies across different compiler versions or
* settings. By exporting only the necessary and well-defined methods and members,
* we minimize the risk of such problems, ensuring a more robust and reliable integration
* with the client applications.
* 
* @version 1.0
* @date 2023-10-27
* @author Secareanu Filip
*/

#include "glophysx/core/core.h"

#include "glophysx/core/window/platforms/windows/wwindow.h"

#include "glophysx/core/layers/layers_container.h"
#include "glophysx/core/gui/gui_layer.h"

/*
* @brief Forward declaration of the main function
* 
* @see entry_point.h
*/
int main(int argc, char** argv);

namespace GLOPHYSX {

	/**
	* @class Application
	* @brief The main class that runs the GLoPhysX engine. It is declared as a singleton
	*
	* This class is responsible for setting up the engine, running the main game loop,
	* handling events and cleaning up upon exit. It should be subclassed by the client
	* application to provide engine-specific functionalities.
	*/ 
	class Application
	{
	public:
		GLOP_API Application();
		GLOP_API ~Application();

		// Method that handles the events received
		GLOP_API void OnEvent(Event& e);
		// Method for pushing layers on the layer stack
		GLOP_API void PushLayer(Layer* layer);
		//Method for pushing overlays on the layer stack
		GLOP_API void PushOverlay(Layer* overlay);

		// Method to get the application class's instance
		GLOP_API static Application& GetInstance();

		// Method to get the active window
		GLOP_API Window& GetWindow();

	private:
		GLOP_API void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		bool m_running;
		Unique<Window> m_window;

		LayersContainer m_layers_container;
		GUILayer* m_gui_layer;

		DeltaTime m_dt;
		float m_previous_time;

	private:
		static Application* s_instance;
		friend int ::main(int argc, char** argv);
	};

	/**
	* @brief Function to create an instance of the application.
	*
	* This function should be defined on the client side, returning an instance
	* of the client's application subclass. The engine will call this function
	* to create and run the application.
	*
	* @return A pointer to the created application instance.
	*/
	Application* CreateApplication();
}
