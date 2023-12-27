#pragma once

#include "application/application.h"

#include "glophysx/debug/debug.h"

#if defined(GLOP_PLATFORM_WINDOWS)

extern GLOPHYSX::Application* GLOPHYSX::CreateApplication(CommandLineArgs args);

int main(int argc, char **argv) {
	GLOPHYSX::Logger::Init();

	GLOP_PROFILER_BEGIN_SESSION("Startup", "GLoPhysX-StartupProfile.json");
	auto app = GLOPHYSX::CreateApplication({argc, argv});
	GLOP_PROFILER_END_SESSION();

	//GLOP_PROFILER_BEGIN_SESSION("Startup", "GLoPhysX-RuntimeProfile.json");
	app->Run();
	//GLOP_PROFILER_END_SESSION();

	GLOP_PROFILER_BEGIN_SESSION("Shutdown", "GLoPhysX-ShutdownProfile.json");
	delete app;
	GLOP_PROFILER_END_SESSION();

	GLOPHYSX::Logger::Shutdown();
}

#endif
