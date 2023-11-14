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
	#define GLOPMOUSE_BUTTON_1         0
	#define GLOPMOUSE_BUTTON_2         1
	#define GLOPMOUSE_BUTTON_3         2
	#define GLOPMOUSE_BUTTON_4         3
	#define GLOPMOUSE_BUTTON_5         4
	#define GLOPMOUSE_BUTTON_6         5
	#define GLOPMOUSE_BUTTON_7         6
	#define GLOPMOUSE_BUTTON_8         7
	#define GLOPMOUSE_BUTTON_LAST      GLOPMOUSE_BUTTON_8
	#define GLOPMOUSE_BUTTON_LEFT      GLOPMOUSE_BUTTON_1
	#define GLOPMOUSE_BUTTON_RIGHT     GLOPMOUSE_BUTTON_2
	#define GLOPMOUSE_BUTTON_MIDDLE    GLOPMOUSE_BUTTON_3
#else
	#error "GloPhysX only supports Windows"
#endif
