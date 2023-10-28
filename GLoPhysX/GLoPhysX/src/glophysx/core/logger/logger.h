#pragma once

#include "glophysx/core/core.h"

#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"

namespace GLOPHYSX {

	constexpr auto CORE_LOGGER_NAME = "CORE";
	constexpr auto CLIENT_LOGGER_NAME = "CLIENT";


	/**
	* @class Logger
	* @brief Centralized and globally accessible logging utility.
	*
	* Logger is crafted solely for static use, ensuring straightforward access
	* to logging functionalities across the entire application without the need
	* for instantiation.
	*
	* In order to maintain binary stability and facilitate seamless integration
	* across DLL boundaries, Logger exports its individual static functions using
	* the GLOP_API macro, instead of exporting the entire class.
	* This approach addresses potential complications associated with template
	* instantiation and memory management when interacting with shared libraries,
	* with spdlog being the utilized logging library in this context.
	*
	* Consequently, Logger avoids the pitfalls of ABI incompatibilities and complex
	* memory management scenarios that can arise from exporting
	* std::shared_ptr<spdlog::logger>. This careful design choice guarantees a robust
	* and safe interface for Logger, ensuring its reliability and integrity across
	* diverse application architectures and DLL interactions.
	*/

	class Logger
	{
	public:
		Logger() = delete;
		~Logger() = delete;

		GLOP_API static void Init();
		GLOP_API static void Shutdown();

		GLOP_API static std::shared_ptr<spdlog::logger> GetCoreLogger();

		GLOP_API static std::shared_ptr<spdlog::logger> GetClientLogger();

	private:
		static std::shared_ptr<spdlog::logger> s_core_logger;
		static std::shared_ptr<spdlog::logger> s_client_logger;
	};

	#define GLOP_CORE_TRACE(...)			GLOPHYSX::Logger::GetCoreLogger()->trace(__VA_ARGS__);
	#define GLOP_CORE_DEBUG(...)			GLOPHYSX::Logger::GetCoreLogger()->debug(__VA_ARGS__);
	#define GLOP_CORE_INFO(...)				GLOPHYSX::Logger::GetCoreLogger()->info(__VA_ARGS__);
	#define GLOP_CORE_WARN(...)				GLOPHYSX::Logger::GetCoreLogger()->warn(__VA_ARGS__);
	#define GLOP_CORE_ERROR(...)			GLOPHYSX::Logger::GetCoreLogger()->error(__VA_ARGS__);
	#define GLOP_CORE_CRITICAL(...)			GLOPHYSX::Logger::GetCoreLogger()->critical(__VA_ARGS__);

	#define GLOP_CLIENT_TRACE(...)			GLOPHYSX::Logger::GetClientLogger()->trace(__VA_ARGS__);
	#define GLOP_CLIENT_DEBUG(...)			GLOPHYSX::Logger::GetClientLogger()->debug(__VA_ARGS__);
	#define GLOP_CLIENT_INFO(...)			GLOPHYSX::Logger::GetClientLogger()->info(__VA_ARGS__);
	#define GLOP_CLIENT_WARN(...)			GLOPHYSX::Logger::GetClientLogger()->warn(__VA_ARGS__);
	#define GLOP_CLIENT_ERROR(...)			GLOPHYSX::Logger::GetClientLogger()->error(__VA_ARGS__);
	#define GLOP_CLIENT_CRITICAL(...)		GLOPHYSX::Logger::GetClientLogger()->critical(__VA_ARGS__);
}

