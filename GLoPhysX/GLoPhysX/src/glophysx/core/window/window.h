/**
* @file window.h
* @brief Header file for the Window class in the GLoPhysX engine.
*
* This file declares the Window class, which serves as an abstract base class for creating and managing windows
* in the GLoPhysX engine. The Window class provides a generic interface for window management, abstracting away
* platform-specific details to ensure code portability. Derived classes should provide implementations tailored
* to specific windowing systems (such as Windows, GLFW, etc.).
*
* The Window class encompasses functions for window initialization, updating, destruction, and event handling.
* It also provides a mechanism to retrieve the native window object, allowing for interoperability with other
* libraries and systems that may require direct access to the underlying windowing system.
*
* Additionally, the file includes a template function `Create`, which facilitates the creation of window objects
* of specific types derived from the Window class. This function returns a unique pointer to the created window,
* ensuring proper memory management and resource cleanup.
*
* Usage of this class typically involves subclassing it to provide implementations for the virtual functions,
* initializing a window object using the `Create` function, and then calling the window’s methods as needed in
* the main application loop.
*
* @see WindowProperties
* @see Window::Create
*
* @version 1.0
* @date 2023-10-27
*/

#pragma once

#include "glophysx/core/core.h"
#include "window_properties.h"
#include "glophysx/events/event.h"

namespace GLOPHYSX {

    /**
     * @brief Abstract base class for window creation and management.
     *
     * Window serves as an interface for creating and handling windows in different
     * environments. It encapsulates all common and platform-independent functionality
     * for window operations.
     */
    class GLOP_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        /**
         * @brief Virtual destructor for safe polymorphic destruction.
         */
        virtual ~Window() = default;

        virtual void Initialize(WindowProperties* wp) = 0;
        virtual void Update() = 0;
        virtual void Destroy() = 0;

        /**
         * @brief Sets the event callback function for window events.
         *
         * @param callback The function to call when an event occurs.
         */
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        virtual void* GetNativeWindow() const = 0;

        int GetWidth() { return properties->width; }
        int GetHeight() { return properties->height; }

        /**
         * @brief Factory method for creating windows of a specific type.
         *
         * This template function allows for the creation of any window type derived from the Window class,
         * encapsulating the object in a unique_ptr to manage its lifecycle automatically.
         *
         * @param wp Pointer to a WindowProperties object with desired window settings.
         * @return A unique_ptr to the created window instance of type WindowType.
         */
        template <typename WindowType>
        static std::unique_ptr<WindowType> Create(WindowProperties* wp)
        {
            return std::make_unique<WindowType>(wp);
        }

    protected:
        /**
        * @brief Invokes methods to set various groups of callbacks.
        *
        * This function calls the three methods responsible for setting up
        * different categories of callbacks: window, keyboard, and mouse.
        * It is intended to be called during window initialization to ensure all
        * necessary callbacks are registered with the window instance.
        */
        void SetCallbacks();

        /**
         * @brief Sets window-specific callbacks.
         *
         * Derived classes must provide the implementation for setting window event callbacks.
         */
        virtual void SetWindowCallbacks() = 0;

        /**
         * @brief Sets keyboard-specific callbacks.
         *
         * Derived classes must provide the implementation for setting keyboard event callbacks.
         */
        virtual void SetKeyCallbacks() = 0;

        /**
         * @brief Sets mouse-specific callbacks.
         *
         * Derived classes must provide the implementation for setting mouse event callbacks.
         */
        virtual void SetMouseCallbacks() = 0;

    protected:
        WindowProperties* properties;
    };
}
