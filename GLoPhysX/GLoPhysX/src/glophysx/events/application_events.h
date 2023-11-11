/**
* @file application_events.h
* @brief Application(window) event classes for the GLOPHYSX engine.
*
* This file defines a set of classes that represent different types of window-related events
* within the GLOPHYSX engine. These events are used to communicate specific changes in window
* state, such as closing, resizing, moving, focusing, and iconifying. The event system allows
* for decoupled communication between the window system and other parts of the engine, which
* can respond to these changes as needed. Each event class inherits from the base Event class
* and provides additional context relevant to the event type it represents.
*
* The specific event classes included are:
* - WindowCloseEvent: Triggered when a window close request is made.
* - WindowResizeEvent: Triggered when a window is resized.
* - WindowMoveEvent: Triggered when a window is moved.
* - WindowFocusEvent: Triggered when a window gains or loses focus.
* - WindowIconifyEvent: Triggered when a window is iconified (minimized) or restored.
*
* These event classes are part of the event dispatching system and can be utilized to handle
* window events in a standardized way throughout the engine. They also provide a consistent
* interface for logging and debugging window state changes.
*
* @version 1.0
* @date 2023-10-27
* @see Event
*/

#pragma once

#include "event.h"

namespace GLOPHYSX {

    /**
    * @class WindowCloseEvent
    * @brief Event triggered when the window is requested to close.
    *
    * This event is dispatched when a window close operation is initiated,
    * for example, when the user clicks the close button on a window or when
    * a close command is issued programmatically.
    */
    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        // Returns the static type of the event for comparison purposes
        static EventType GetStaticType() { return EventType::WindowClose; }

        // Returns the dynamic type of the event for dispatching
        EventType GetType() const override { return GetStaticType(); }
        // Returns a string name of the event for logging or debugging
        const char* GetName() const override { return "WindowClose"; }

        int GetCategoryFlags() const override { return EventCategoryApplication; }
    };

    /**
     * @class WindowResizeEvent
     * @brief Event triggered when the window is resized.
     *
     * This event contains the new width and height of the window after a resize
     * operation. It allows listeners to adjust resources or layouts based on the
     * new window size.
     *
     * @param width The new width of the window.
     * @param height The new height of the window.
     */
    class WindowResizeEvent : public Event {
    public:
        // Constructor is deleted to prevent default instantiation.
        WindowResizeEvent() = delete;
        WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {}

        static EventType GetStaticType() { return EventType::WindowResize; }

        EventType GetType() const override { return GetStaticType(); }
        const char* GetName() const override { return "WindowResize"; }

        int GetCategoryFlags() const override { return EventCategoryApplication; }

        // Provides a text representation of the event data for logging
        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_width << ", " << m_height;
            return ss.str();
        }

        inline int GetWidth() { return m_width; }
        inline int GetHeight() { return m_height; }

    private:
        int m_width;   // The new width of the window
        int m_height;  // The new height of the window
    };

    /**
     * @class WindowMoveEvent
     * @brief Event triggered when the window is moved to a new position on screen.
     *
     * This event provides the new X and Y coordinates of the upper-left corner of the
     * window. It is useful for tracking the window's position or for multi-window management.
     *
     * @param new_x The new X-coordinate of the window.
     * @param new_y The new Y-coordinate of the window.
     */
    class WindowMoveEvent : public Event {
    public:
        // Constructor is deleted to prevent default instantiation.
        WindowMoveEvent() = delete;
        WindowMoveEvent(int new_x, int new_y) : m_new_x(new_x), m_new_y(new_y) {}

        static EventType GetStaticType() { return EventType::WindowMove; }

        EventType GetType() const override { return GetStaticType(); }
        const char* GetName() const override { return "WindowMove"; }

        int GetCategoryFlags() const override { return EventCategoryApplication; }

        // Outputs a string with the new window position for logging
        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowMoveEvent: " << m_new_x << ", " << m_new_y;
            return ss.str();
        }

    private:
        int m_new_x;  // The new X-coordinate after the window move
        int m_new_y;  // The new Y-coordinate after the window move
    };

    /**
     * @class WindowFocusEvent
     * @brief Event triggered when the window gains or loses focus.
     *
     * An instance of this event signifies that the window has either become the
     * foreground window or has been relegated to the background. The focus state
     * is encoded as an integer.
     *
     * @param focus The focus state of the window, typically represented as a boolean.
     */
    class WindowFocusEvent : public Event {
    public:
        // Constructor is deleted to prevent default instantiation.
        WindowFocusEvent() = delete;
        WindowFocusEvent(int focus) : m_focused(focus) {}

        static EventType GetStaticType() { return EventType::WindowFocus; }

        EventType GetType() const override { return GetStaticType(); }
        const char* GetName() const override { return "WindowFocus"; }

        int GetCategoryFlags() const override { return EventCategoryApplication; }

        // Converts the event focus state to a string for output or logging
        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowFocusEvent: " << (m_focused ? "focused" : "unfocused");
            return ss.str();
        }

    private:
        int m_focused; // Focus state: non-zero for focused, zero for unfocused
    };

    /**
     * @class WindowIconifyEvent
     * @brief Event triggered when the window is iconified (minimized) or restored.
     *
     * This event indicates a change in the window's iconification state. Listeners can
     * use this to pause or resume certain operations when the window is minimized or
     * to save and restore window state as needed.
     *
     * @param iconify The iconification state of the window, typically represented as a boolean.
     */
    class WindowIconifyEvent : public Event {
    public:
        // Constructor is deleted to prevent default instantiation.
        WindowIconifyEvent() = delete;
        WindowIconifyEvent(int iconify) : m_iconified(iconify) {}

        static EventType GetStaticType() { return EventType::WindowIconify; }

        EventType GetType() const override { return GetStaticType(); }
        const char* GetName() const override { return "WindowIconify"; }

        int GetCategoryFlags() const override { return EventCategoryApplication; }

        // Generates a string describing the iconification event for logging
        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowIconifyEvent: " << (m_iconified ? "iconified" : "restored");
            return ss.str();
        }

    private:
        int m_iconified; // Iconification state: non-zero for iconified, zero for normal/restored
    };
}
