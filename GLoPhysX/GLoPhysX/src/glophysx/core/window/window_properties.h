#pragma once

#include "gxpch.h"

typedef struct window_properties WindowProperties;
struct window_properties {
	const char* title;

	unsigned int width;
	unsigned int height;
	double aspect_ration;

	window_properties(
		const char* title = "GLoPhysX Engine",

		unsigned int width = 1600,
		unsigned int height = 900,
		double aspect_ration = 0.0f
	) : title(title),
		width(width), height(height), aspect_ration((double)width / height) {}
};
