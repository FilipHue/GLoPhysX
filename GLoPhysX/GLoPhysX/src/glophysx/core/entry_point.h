#pragma once

#if defined(GLOP_PLATFORM_WINDOWS)

extern GLOPHYSX::Application* GLOPHYSX::CreateApplication();

int main(int argc, char **argv) {
	GLOPHYSX::Logger::Init();

	GLOP_CORE_TRACE("Testing core logger - trace...");
	GLOP_CORE_DEBUG("Testing core logger - debug...");
	GLOP_CORE_INFO("Testing core logger - info...");
	GLOP_CORE_WARN("Testing core logger - warn...");
	GLOP_CORE_ERROR("Testing core logger - error...");
	GLOP_CORE_CRITICAL("Testing core logger - critical...");

	GLOP_CLIENT_TRACE("Testing client logger - trace...");
	GLOP_CLIENT_DEBUG("Testing client logger - debug...");
	GLOP_CLIENT_INFO("Testing client logger - info...");
	GLOP_CLIENT_WARN("Testing client logger - warn...");
	GLOP_CLIENT_ERROR("Testing client logger - error...");
	GLOP_CLIENT_CRITICAL("Testing client logger - critical...");

	auto app = GLOPHYSX::CreateApplication();

	app->Run();

	delete app;
}

#endif	