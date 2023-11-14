#pragma once

/*
* @file keycodes.h
* @brief File that contains platform dependent keycodes
* 
* Here you put the keycodes of the platform that you used for creating
* the window
*/

#ifdef GLOP_PLATFORM_WINDOWS

	// GLFW keycodes
	#define GLOP_KEY_SPACE              32
	#define GLOP_KEY_APOSTROPHE         39  /* ' */
	#define GLOP_KEY_COMMA              44  /* , */
	#define GLOP_KEY_MINUS              45  /* - */
	#define GLOP_KEY_PERIOD             46  /* . */
	#define GLOP_KEY_SLASH              47  /* / */
	#define GLOP_KEY_0                  48
	#define GLOP_KEY_1                  49
	#define GLOP_KEY_2                  50
	#define GLOP_KEY_3                  51
	#define GLOP_KEY_4                  52
	#define GLOP_KEY_5                  53
	#define GLOP_KEY_6                  54
	#define GLOP_KEY_7                  55
	#define GLOP_KEY_8                  56
	#define GLOP_KEY_9                  57
	#define GLOP_KEY_SEMICOLON          59  /* ; */
	#define GLOP_KEY_EQUAL              61  /* = */
	#define GLOP_KEY_A                  65
	#define GLOP_KEY_B                  66
	#define GLOP_KEY_C                  67
	#define GLOP_KEY_D                  68
	#define GLOP_KEY_E                  69
	#define GLOP_KEY_F                  70
	#define GLOP_KEY_G                  71
	#define GLOP_KEY_H                  72
	#define GLOP_KEY_I                  73
	#define GLOP_KEY_J                  74
	#define GLOP_KEY_K                  75
	#define GLOP_KEY_L                  76
	#define GLOP_KEY_M                  77
	#define GLOP_KEY_N                  78
	#define GLOP_KEY_O                  79
	#define GLOP_KEY_P                  80
	#define GLOP_KEY_Q                  81
	#define GLOP_KEY_R                  82
	#define GLOP_KEY_S                  83
	#define GLOP_KEY_T                  84
	#define GLOP_KEY_U                  85
	#define GLOP_KEY_V                  86
	#define GLOP_KEY_W                  87
	#define GLOP_KEY_X                  88
	#define GLOP_KEY_Y                  89
	#define GLOP_KEY_Z                  90
	#define GLOP_KEY_LEFT_BRACKET       91  /* [ */
	#define GLOP_KEY_BACKSLASH          92  /* \ */
	#define GLOP_KEY_RIGHT_BRACKET      93  /* ] */
	#define GLOP_KEY_GRAVE_ACCENT       96  /* ` */
	#define GLOP_KEY_WORLD_1            161 /* non-US #1 */
	#define GLOP_KEY_WORLD_2            162 /* non-US #2 */

	/* Function keys */
	#define GLOP_KEY_ESCAPE             256
	#define GLOP_KEY_ENTER              257
	#define GLOP_KEY_TAB                258
	#define GLOP_KEY_BACKSPACE          259
	#define GLOP_KEY_INSERT             260
	#define GLOP_KEY_DELETE             261
	#define GLOP_KEY_RIGHT              262
	#define GLOP_KEY_LEFT               263
	#define GLOP_KEY_DOWN               264
	#define GLOP_KEY_UP                 265
	#define GLOP_KEY_PAGE_UP            266
	#define GLOP_KEY_PAGE_DOWN          267
	#define GLOP_KEY_HOME               268
	#define GLOP_KEY_END                269
	#define GLOP_KEY_CAPS_LOCK          280
	#define GLOP_KEY_SCROLL_LOCK        281
	#define GLOP_KEY_NUM_LOCK           282
	#define GLOP_KEY_PRINT_SCREEN       283
	#define GLOP_KEY_PAUSE              284
	#define GLOP_KEY_F1                 290
	#define GLOP_KEY_F2                 291
	#define GLOP_KEY_F3                 292
	#define GLOP_KEY_F4                 293
	#define GLOP_KEY_F5                 294
	#define GLOP_KEY_F6                 295
	#define GLOP_KEY_F7                 296
	#define GLOP_KEY_F8                 297
	#define GLOP_KEY_F9                 298
	#define GLOP_KEY_F10                299
	#define GLOP_KEY_F11                300
	#define GLOP_KEY_F12                301
	#define GLOP_KEY_F13                302
	#define GLOP_KEY_F14                303
	#define GLOP_KEY_F15                304
	#define GLOP_KEY_F16                305
	#define GLOP_KEY_F17                306
	#define GLOP_KEY_F18                307
	#define GLOP_KEY_F19                308
	#define GLOP_KEY_F20                309
	#define GLOP_KEY_F21                310
	#define GLOP_KEY_F22                311
	#define GLOP_KEY_F23                312
	#define GLOP_KEY_F24                313
	#define GLOP_KEY_F25                314
	#define GLOP_KEY_KP_0               320
	#define GLOP_KEY_KP_1               321
	#define GLOP_KEY_KP_2               322
	#define GLOP_KEY_KP_3               323
	#define GLOP_KEY_KP_4               324
	#define GLOP_KEY_KP_5               325
	#define GLOP_KEY_KP_6               326
	#define GLOP_KEY_KP_7               327
	#define GLOP_KEY_KP_8               328
	#define GLOP_KEY_KP_9               329
	#define GLOP_KEY_KP_DECIMAL         330
	#define GLOP_KEY_KP_DIVIDE          331
	#define GLOP_KEY_KP_MULTIPLY        332
	#define GLOP_KEY_KP_SUBTRACT        333
	#define GLOP_KEY_KP_ADD             334
	#define GLOP_KEY_KP_ENTER           335
	#define GLOP_KEY_KP_EQUAL           336
	#define GLOP_KEY_LEFT_SHIFT         340
	#define GLOP_KEY_LEFT_CONTROL       341
	#define GLOP_KEY_LEFT_ALT           342
	#define GLOP_KEY_LEFT_SUPER         343
	#define GLOP_KEY_RIGHT_SHIFT        344
	#define GLOP_KEY_RIGHT_CONTROL      345
	#define GLOP_KEY_RIGHT_ALT          346
	#define GLOP_KEY_RIGHT_SUPER        347
	#define GLOP_KEY_MENU               348
#else
	#error "GloPhysX only supports Windows"
#endif
