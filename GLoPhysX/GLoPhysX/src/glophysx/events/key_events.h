/**
* @file key_events.h
* @brief Key event classes for the GLOPHYSX engine.
*
* This header defines classes for key-related events in the GLOPHYSX engine. Key events are used
* to communicate keyboard actions performed by the user, such as pressing and releasing keys,
* as well as typing characters when the window has input focus. These events provide the engine
* with information necessary to respond to keyboard input in a consistent and centralized manner.
*
* The classes defined in this file are:
* - KeyPressEvent: Represents an event where a key is pressed. It includes information about
*   the keycode, any modifier keys that are active, and the repeat state indicating whether
*   the key press event is due to keyboard repeat.
* - KeyReleaseEvent: Represents an event where a key is released. Similar to KeyPressEvent, it
*   carries details about the keycode and active modifier keys.
* - KeyTypedEvent: Represents an event where a character is typed, i.e., resulting from key
*   presses that produce a character input according to the current keyboard layout and state.
*   This event specifically carries the Unicode character resulting from the key press.
*
* Each event is derived from the base Event class and provides additional context-specific
* to key input, facilitating easy handling and processing of keyboard actions within the
* engine's event system. These events are part of a broader system that supports polling
* and event subscription for keyboard input, enabling interactive application behavior and
* control schemes.
* 
* @version 1.0
* @date 2023-10-27
* @see Event
*/

#pragma once

#include "event.h"

namespace GLOPHYSX {

    /**
     * @class KeyPressEvent
     * @brief Event class for a key press action.
     *
     * This class encapsulates the details of a key press action and is used to notify interested
     * parties when a key is pressed on the keyboard. It contains the key code, modifier bits, and
     * repeat count for the key press event.
     */
    class KeyPressEvent : public Event {
    public:
        // Constructor is deleted to prevent default instantiation.
        KeyPressEvent() = delete;
        KeyPressEvent(int keycode, int mods, int repeat) : m_keycode(keycode), m_mods(mods), m_repeat(repeat) {};

        static EventType GetStaticType() { return EventType::KeyPress; }
        EventType GetType() const override { return GetStaticType(); }

        const char* GetName() const override { return "KeyPress"; }

        int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

        // Outputs a formatted string containing the event details.
        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressEvent: " << m_keycode << ", mods: " << m_mods << ", repeat: " << m_repeat;
            return ss.str();
        }

        inline int GetKeycode() { return m_keycode; }

    private:
        int m_keycode; // The key code of the pressed key.
        int m_mods;    // Modifier keys state during the event.
        int m_repeat;  // The repeat count for the event if the key was held down.
    };

    /**
     * @class KeyReleaseEvent
     * @brief Event class for a key release action.
     *
     * Represents the action of a key being released on the keyboard. This class captures the state
     * of the key and the modifier keys at the time of the release.
     */
    class KeyReleaseEvent : public Event {
    public:
        // Constructor is deleted to prevent default instantiation.
        KeyReleaseEvent() = delete;
        KeyReleaseEvent(int keycode, int mods) : m_keycode(keycode), m_mods(mods) {};

        static EventType GetStaticType() { return EventType::KeyRelease; }
        EventType GetType() const override { return GetStaticType(); }

        const char* GetName() const override { return "KeyRelease"; }

        int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

        // Outputs a formatted string containing the event details.
        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleaseEvent: " << m_keycode << ", mods: " << m_mods;
            return ss.str();
        }

        inline int GetKeycode() { return m_keycode; }

    private:
        int m_keycode; // The key code of the released key.
        int m_mods;    // Modifier keys state during the event.
    };

    /**
     * @class KeyTypedEvent
     * @brief Event class for character typing.
     *
     * This class is used to represent the action of a character being typed on the keyboard. It is
     * used in contexts where text input is necessary, distinct from simple key presses which may not
     * always correspond to a character depending on the state of the modifier keys and the keyboard layout.
     */
    class KeyTypedEvent : public Event {
    public:
        // Constructor is deleted to prevent default instantiation.
        KeyTypedEvent() = delete;
        KeyTypedEvent(int unicode_key) : m_unicode_key(unicode_key) {};

        static EventType GetStaticType() { return EventType::KeyTyped; }
        EventType GetType() const override { return GetStaticType(); }

        const char* GetName() const override { return "KeyTyped"; }

        int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

        // Outputs a formatted string containing the event details.
        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: unicode: " << m_unicode_key;
            return ss.str();
        }

        inline int GetUnicodeKey() { return m_unicode_key; }

    private:
        int m_unicode_key; // The Unicode key code of the typed character.
    };
}
