/**
* @file input.h
* @brief Input abstraction for the GLoPhysX engine.
*
* This file defines the Input class interface for querying keyboard and mouse state. The Input class
* serves as an abstract base for a singleton implementation that provides static access methods wrapped
* around virtual protected methods, which are then implemented by platform-specific subclasses.
* This design ensures that input querying can be done consistently across different platforms while
* allowing for flexibility in the actual input processing implementation.
*
* Usage of this class involves calling the static methods like `Input::IsKeyPressed` or `Input::GetMouseX`
* to get the current state of the input devices. The actual state checking is deferred to the subclass
* instance that the static `s_instance` pointer refers to, ensuring that only one input system instance is
* managing state at any time.
*
* @version 1.0
* @date 2023-10-27
*/

#pragma once

#include "glophysx/core/core.h"

namespace GLOPHYSX {

	/**
	* @class Input
	* @brief Abstract class for managing input across the GLoPhysX engine.
	*
	* This class provides a static interface for querying the current input state. It should be
	* subclassed by a concrete implementation that provides platform-specific input functionality.
	* The class allows querying of keyboard and mouse states as a singleton, delegating to protected
	* virtual methods for actual platform-specific state checks.
	*/
	class Input {
	public:
		GLOP_API inline static bool IsKeyPressed(int keycode) { return s_instance->PIsKeyPressed(keycode); }

		GLOP_API inline static bool IsMouseButtonPressed(int button) { return s_instance->PIsMouseButtonPressed(button); }
		GLOP_API inline static double GetMouseX() { return s_instance->PGetMouseX(); }
		GLOP_API inline static double GetMouseY(int button) { return s_instance->PGetMouseY(); }

	protected:
		virtual bool PIsKeyPressed(int keycode) = 0;

		virtual bool PIsMouseButtonPressed(int button) = 0;
		virtual double PGetMouseX() = 0;
		virtual double PGetMouseY() = 0;

	private:
		static Input* s_instance;
	};
}
