#pragma once
/**
* @file graphics_context.h
* @brief Declaration of the GraphicsContext class.
*
* The GraphicsContext class defines an interface for graphics rendering contexts in GLoPhysX. It serves
* as the base class for specific graphics context implementations, such as OpenGL or DirectX. The interface
* includes methods for context initialization, buffer swapping, and context destruction.
* It can be extended with other functionalities, depending on the renderer used.
*
* @version 1.0
* @date 2023-10-27
* @author Secareanu Filip
*/

#include "glophysx/core/core.h"

namespace GLOPHYSX {

	namespace RENDERING {

		/**
		* @class GraphicsContext
		* @brief Abstract class representing a graphics rendering context.
		*
		* GraphicsContext is an abstract class defining the common interface for graphics rendering contexts in GLoPhysX.
		* It includes pure virtual methods for initializing the context, swapping buffers, and destroying the context.
		*/
		class GraphicsContext
		{
		public:
			GLOP_API virtual ~GraphicsContext() = default;

			/**
			* @brief Initializes the graphics rendering context.
			*
			* This method sets up the necessary state for the graphics context. It is called after the context
			* has been created and is responsible for preparing the context for rendering.
			*/
			GLOP_API virtual void Init() = 0;
			/**
			* @brief Swaps the front and back buffers of the rendering context.
			*
			* This method is responsible for presenting the rendered frame to the screen. It swaps the front
			* and back buffers of the rendering context, displaying the newly rendered frame.
			*/
			GLOP_API virtual void SwapBuffers() = 0;
			/**
			* @brief Destroys the graphics rendering context.
			*
			* This method performs cleanup operations for the graphics context. It may involve releasing
			* resources, deleting shaders, or performing other tasks to ensure a clean shutdown.
			*/
			GLOP_API virtual void Destroy() = 0;

			/**
			* @brief Creates a graphics context for the specified window.
			*
			* This static method creates an instance of a graphics context based on the provided window handle.
			* The specific type of context created depends on the underlying graphics API in use.
			*
			* @param window A pointer or handle to the window associated with the graphics context.
			* @return A unique pointer to the created graphics context.
			*/
			GLOP_API static Unique<GraphicsContext> Create(void* window);
		};
	}
}
