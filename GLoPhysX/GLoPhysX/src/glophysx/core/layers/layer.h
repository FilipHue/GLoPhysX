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
*/

#pragma once

#include "glophysx/core/core.h"
#include "glophysx/events/event.h"

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

		GLOP_API virtual void OnAtach() {};
		GLOP_API virtual void OnDetach() {};
		GLOP_API virtual void OnUpdate() {};
		GLOP_API virtual void OnEvent(Event& event) {};
		GLOP_API virtual void OnGUIRender() {};

	protected:
		std::string m_name;
	};
}
