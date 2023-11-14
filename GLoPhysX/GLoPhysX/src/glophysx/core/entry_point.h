#pragma once

#include "glophysx/core/application/application.h"

#if defined(GLOP_PLATFORM_WINDOWS)

extern GLOPHYSX::Application* GLOPHYSX::CreateApplication();

int main(int argc, char **argv) {
	GLOPHYSX::Logger::Init();

	auto app = GLOPHYSX::CreateApplication();

	app->Run();

	delete app;
}

#endif
