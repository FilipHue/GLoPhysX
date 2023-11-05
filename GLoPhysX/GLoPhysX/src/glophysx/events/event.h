/**
* @file event.h
* @brief Header file defining the Event base class and EventDispatcher in the GLoPhysX engine.
*
* This file contains the declaration of the Event base class, which is the foundation for all event classes
* used within the GLoPhysX engine. It also includes the definition of the EventDispatcher class, a utility
* for dispatching events to their corresponding event handlers based on the event type.
*
* The Event class defines a common interface for events that allows querying their type and name, and also
* includes a flag to mark an event as handled. The EventDispatcher provides a static method for dispatching
* events to specific functions intended to process events of a certain type, using template specialization.
*
* @version 1.0
* @date 2023-10-27
*/

#pragma once

#include "gxpch.h"

namespace GLOPHYSX {

	/**
	* @enum EventType
	* @brief Enumerates the types of events that can be handled by the GLoPhysX engine.
	*
	* This enumeration defines a list of event types, including window events, keyboard events,
	* and mouse events. These event types are used to identify the specific class of an event
	* at runtime for appropriate dispatch and handling.
	*/
	typedef enum class event_type {
		None,
		WindowClose, WindowResize, WindowMove, WindowFocus, WindowIconify,
		KeyPress, KeyRelease, KeyTyped,
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
	} EventType;

	/**
	* @class Event
	* @brief Abstract base class for events in the GLoPhysX engine.
	*
	* Event serves as an abstract base class for all events within the GLoPhysX engine, providing
	* a common interface and base functionality for event handling. Derived classes are expected to
	* provide implementations for the virtual methods to facilitate event identification and processing.
	*/
	class Event {
	public:
		virtual ~Event() = default;

		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;

		virtual std::string ToString() const { return GetName(); }

	public:
		bool m_handled = false;

	private:
	};

	/**
	 * @class EventDispatcher
	 * @brief A helper class that dispatches events to appropriate event handlers.
	 *
	 * EventDispatcher is a static class that provides a mechanism to dispatch events based
	 * on their type. It is used to check if an event is of a certain type and then convert
	 * it to that type and call the associated handler. This allows for a type-safe way of
	 * processing events.
	 */
	class EventDispatcher {
	public:
		EventDispatcher() = delete;	// Prevents instantiation of this static class.

		/**
		* @brief Dispatches an event to the given handler if the event is of type T.
		*
		* This template method checks if the given event is of the template type T and, if so,
		* casts it to that type and calls the given handler function on it.
		*
		* @tparam T The type of the event to handle.
		* @tparam F The type of the function or callable to process the event.
		* @param e The event to dispatch.
		* @param func The function or callable that handles the event.
		*/
		template<typename T, typename F>
		static void Dispatch(Event& e, const F& func) {
			if (e.GetType() == T::GetStaticType()) {
				e.m_handled |= func(static_cast<T&>(e));
			}
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
