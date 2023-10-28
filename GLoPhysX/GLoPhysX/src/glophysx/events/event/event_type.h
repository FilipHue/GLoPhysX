#pragma once

enum class EventType {
	None,
	WindowClose, Windowesize, WindowFocus, WindowLostFocus, WindowMoved,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};