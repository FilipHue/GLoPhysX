#pragma once
/**
* @file Layer.h
* @brief Layer system for GLOPHYSX engine.
*
* This file contains the declaration of the Layer class, which is part of the
* core layering system in the GLOPHYSX engine. Layers represent a level of abstraction
* to manage the update and event handling sequence of the engine's runtime.
* Each layer has a name and can respond to events, be attached/detached, and updated
* during the application's lifecycle. The class is designed to be extended to create
* specialized layers with specific behaviors for various aspects of the engine, such as
* rendering, input processing, or post-process effects management.
*
* @version 1.0
* @date 2023-10-27
* @author Secareanu Filip
*/

#include "glophysx/core/core.h"
#include "glophysx/core/events/event.h"
#include "glophysx/core/time/time.h"

namespace GLOPHYSX {

	/**
	* @class Layer
	* @brief Base class for layers in the GLOPHYSX engine.
	*
	* The Layer class represents a discrete layer of functionality that can be
	* independently updated and can handle events. This class should be subclassed to create
	* specific layers for different aspects of an application, like gameplay logic, user
	* interface, or background services.
	*/
	class Layer
	{
	public:
		GLOP_API Layer(const std::string& name = "Layer") : m_name(name) {};
		GLOP_API virtual ~Layer() = default;

		// Method that defines what happens when you first introduce the layer in the layer stack
		GLOP_API virtual void OnAttach() {};
		// Method that defines what happens when you take the layer from the layer stack
		GLOP_API virtual void OnDetach() {};
		// Method to update the layer
		GLOP_API virtual void OnUpdate(DeltaTime dt) {};
		// Method for the layer to handle events
		GLOP_API virtual void OnEvent(Event& event) {};

		// Method used to render GUI, if it exists
		GLOP_API virtual void OnGUIRender() {};

	protected:
		std::string m_name; // Layer's name (for debugging purposes)
	};
}
