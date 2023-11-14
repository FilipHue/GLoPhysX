#pragma once
/**
* @file mouse_events.h
* @brief Header file defining the mouse-related event types in the GLOPHYSX framework.
*
* This file contains the declarations for mouse event handling within the GLOPHYSX framework,
* providing a structured way to handle various mouse interactions, including button presses,
* button releases, movements, and scrolling actions.
*
* The mouse event system enhances interaction capabilities for GUI components or game controls,
* offering granular control over mouse input and integration with the GLOPHYSX event dispatch system.
* This file should be included where mouse event processing is needed.
* 
* @see Event
* @version 1.0
* @date 2023-10-27
* @author Secareanu Filip
*/

#include "event.h"

namespace GLOPHYSX {

    /**
    * @class MouseButtonPressEvent
    * @brief Event class for a mouse button press action.
    *
    * Encapsulates the details of a mouse button press action. It stores the button type and state
    * of the modifier keys at the time of the press.
    */
    class MouseButtonPressEvent : public Event {
    public:
        // Constructor is deleted to prevent default instantiation.
        MouseButtonPressEvent() = delete;
        MouseButtonPressEvent(int button, int mods) : m_button(button), m_mods(mods) {};

        static EventType GetStaticType() { return EventType::MouseButtonPress; }

        EventType GetType() const override { return GetStaticType(); }
        const char* GetName() const override { return "MouseButtonPress"; }
        int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressEvent: button=" << m_button << ", mods=" << m_mods;
            return ss.str();
        }

        inline int GetMouseButton() { return m_button; }

    private:
        int m_button;  // Identifier for the mouse button that was pressed.
        int m_mods;    // Modifier keys state during the event.
    };

    /**
     * @class MouseButtonReleaseEvent
     * @brief Event class for a mouse button release action.
     *
     * Represents the action of a mouse button being released. Holds data for the button released
     * and any modifier keys active at that moment.
     */
    class MouseButtonReleaseEvent : public Event {
    public:
        // Constructor is deleted to prevent default instantiation.
        MouseButtonReleaseEvent() = delete;
        MouseButtonReleaseEvent(int button, int mods) : m_button(button), m_mods(mods) {};

        static EventType GetStaticType() { return EventType::MouseButtonRelease; }

        EventType GetType() const override { return GetStaticType(); }
        const char* GetName() const override { return "MouseButtonRelease"; }
        int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleaseEvent: button=" << m_button << ", mods=" << m_mods;
            return ss.str();
        }

        inline int GetMouseButton() { return m_button; }

    private:
        int m_button;  // Identifier for the mouse button that was released.
        int m_mods;    // Modifier keys state during the event.
    };

    /**
     * @class MouseMoveEvent
     * @brief Event class for mouse movement.
     *
     * Encapsulates details when the mouse is moved. It provides the new position of the cursor in
     * the X and Y coordinates relative to the application window.
     */
    class MouseMoveEvent : public Event {
    public:
        // Constructor is deleted to prevent default instantiation.
        MouseMoveEvent() = delete;
        MouseMoveEvent(double x_pos, double y_pos) : m_x_pos(x_pos), m_y_pos(y_pos) {};

        static EventType GetStaticType() { return EventType::MouseMove; }

        EventType GetType() const override { return GetStaticType(); }
        const char* GetName() const override { return "MouseMove"; }
        int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMoveEvent: x_pos=" << m_x_pos << ", y_pos=" << m_y_pos;
            return ss.str();
        }

        inline double GetXPos() { return m_x_pos; }
        inline double GetYPos() { return m_y_pos; }

    private:
        double m_x_pos; // The new X position of the mouse cursor.
        double m_y_pos; // The new Y position of the mouse cursor.
    };

    /**
     * @class MouseScrollEvent
     * @brief Event class for mouse scroll actions.
     *
     * Captures the scroll wheel movement on the mouse. Provides the scroll offsets along the X and
     * Y axes, which can be used to implement scrolling functionality in an application.
     */
    class MouseScrollEvent : public Event {
    public:
        // Constructor is deleted to prevent default instantiation.
        MouseScrollEvent() = delete;
        MouseScrollEvent(double x_offset, double y_offset) : m_x_offset(x_offset), m_y_offset(y_offset) {};

        static EventType GetStaticType() { return EventType::MouseScroll; }

        EventType GetType() const override { return GetStaticType(); }
        const char* GetName() const override { return "MouseScroll"; }
        int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrollEvent: x_offset=" << m_x_offset << ", y_offset=" << m_y_offset;
            return ss.str();
        }

        inline double GetXOffset() { return m_x_offset; }
        inline double GetYOffset() { return m_y_offset; }

    private:
        double m_x_offset; // The scroll offset along the X-axis.
        double m_y_offset; // The scroll offset along the Y-axis.
    };
}
