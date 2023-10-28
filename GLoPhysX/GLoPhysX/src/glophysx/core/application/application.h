/**
 * @file Application.h
 * @brief This file contains the declaration of the Application class and the CreateApplication function.
 *
 * The Application class represents the core of the GLoPhysX engine. It provides
 * the necessary functionality to initialize, run, and shut down the engine. This
 * class is intended to be subclassed by the client application to provide
 * custom behavior.
 */

#pragma once

#include "glophysx/core/core.h"

namespace GLOPHYSX {

	/**
	* @class Application
	* @brief The main class that runs the GLoPhysX engine.
	*
	* This class is responsible for setting up the engine, running the main game loop,
	* handleing events and cleaning up upon exit. It should be subclassed by the client
	* application to provide game-specific functionality.
	*/ 
	class GLOP_API Application
	{
	public:
		Application();
		~Application();

		void Run();
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
