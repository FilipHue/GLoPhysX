#pragma once

/*
* Define GLOP_API for DLL export/import
* Define GLOP_INLINE_API for inline function for clear behaviour
* 
* Define GLOP_VERSION_MAJOR, GLOP_VERSION_MINOR anf GLOP_VERSION_PATCH for version control and logging
*/

#if defined(GLOP_PLATFORM_WINDOWS)
	#if defined(GLOP_BUILD_DLL)
		#define GLOP_API __declspec(dllexport)
	#else
		#define GLOP_API __declspec(dllimport)
	#endif
#else
	#error "GLoPhysX only supports Windows!"
#endif

#define GLOP_VERSION_MAJOR 1
#define GLOP_VERSION_MINOR 0
#define GLOP_VERSION_PATCH 0
