#pragma once

/*
* @file mouse_codes.h
* @brief File that contains platform dependent mouse codes
*
* Here you put the mouse codes of the platform that you used for creating
* the window
*/

#ifdef GLOP_PLATFORM_WINDOWS

	// GLFW codes
	#define GLOP_MOUSE_BUTTON_1         0
	#define GLOP_MOUSE_BUTTON_2         1
	#define GLOP_MOUSE_BUTTON_3         2
	#define GLOP_MOUSE_BUTTON_4         3
	#define GLOP_MOUSE_BUTTON_5         4
	#define GLOP_MOUSE_BUTTON_6         5
	#define GLOP_MOUSE_BUTTON_7         6
	#define GLOP_MOUSE_BUTTON_8         7
	#define GLOP_MOUSE_BUTTON_LAST      GLOP_MOUSE_BUTTON_8
	#define GLOP_MOUSE_BUTTON_LEFT      GLOP_MOUSE_BUTTON_1
	#define GLOP_MOUSE_BUTTON_RIGHT     GLOP_MOUSE_BUTTON_2
	#define GLOP_MOUSE_BUTTON_MIDDLE    GLOP_MOUSE_BUTTON_3
#else
	#error "GloPhysX only supports Windows"
#endif
