#pragma once

#if defined(GLOP_PLATFORM_WINDOWS)
#if defined(GLOP_BUILD_DLL)
#define GLOP_API __declspec(dllexport)
#else
#define GLOP_API __declspec(dllimport)
#endif
#else
#error "GLoPhysX only supports Windows!"
#endif