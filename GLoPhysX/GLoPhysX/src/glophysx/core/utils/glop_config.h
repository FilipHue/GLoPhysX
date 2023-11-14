#pragma once

/*
* Define GLOP_API for DLL export/import, if the engine is linked dynamically
* 
* Define GLOP_VERSION_MAJOR, GLOP_VERSION_MINOR and GLOP_VERSION_PATCH for version control and logging
*/

#if defined(GLOP_PLATFORM_WINDOWS)
	#if defined(GLOP_DYNAMIC_LIB)
		#if defined(GLOP_BUILD_DLL)
			#define GLOP_API __declspec(dllexport)
		#else
			#define GLOP_API __declspec(dllimport)
		#endif
	#else
		#define GLOP_API
	#endif
#else
	#error "GLoPhysX only supports Windows!"
#endif

#define GLOP_VERSION_MAJOR 1
#define GLOP_VERSION_MINOR 0
#define GLOP_VERSION_PATCH 0
