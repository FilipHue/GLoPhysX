#pragma once

// Platform detection

/* Windows */
#if defined(_WIN32)
    /* Windows x64 */
#if defined(_WIN64)
#define GLOP_PLATFORM_WINDOWS
#else
    /* Windows x86 */
#error "GLoPhysX doesn't support x86 builds!"
#endif

/* Apple platforms */
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE || TARGET_OS_MAC
#error "GLoPhysX doesn't support iOS, iOS Simulator, or macOS!"
#else
#error "Unknown Apple platform!"
#endif

/* Android */
#elif defined(__ANDROID__)
#error "GLoPhysX doesn't support Android!"

/* Linux */
#elif defined(__linux__)
#error "GLoPhysX doesn't support Linux!"

/* Unknown platform */
#else
#error "Unknown platform!"
#endif
