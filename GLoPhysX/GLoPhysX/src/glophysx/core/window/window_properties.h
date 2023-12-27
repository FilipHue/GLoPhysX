#pragma once

namespace GLOPHYSX {

	struct WindowProperties {
		const char* title;

		unsigned int width;
		unsigned int height;
		double aspect_ration;

		WindowProperties(
			const char* title = "GLoPhysX Engine",

			unsigned int width = 1600,
			unsigned int height = 900,
			double aspect_ration = 0.0f
		) : title(title),
			width(width), height(height), aspect_ration((double)width / height) {}
	};
}
