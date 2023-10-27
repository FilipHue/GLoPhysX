#pragma once

#include "core.h"

#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"

#include <vector>
#include <memory>

namespace GLOPHYSX {

	constexpr auto CORE_LOGGER_NAME = "CORE";
	constexpr auto CLIENT_LOGGER_NAME = "CLIENT";

	class Logger
	{
	public:
		Logger() = delete;
		~Logger() = delete;

		GLOP_API static void Init();
		GLOP_API static void Shutdown();

		GLOP_API inline static std::shared_ptr<spdlog::logger> GetCoreLogger() {
			return s_core_logger;
		}

		GLOP_API inline static std::shared_ptr<spdlog::logger> GetClientLogger() {
			return s_client_logger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_core_logger;
		static std::shared_ptr<spdlog::logger> s_client_logger;
	};
}

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
