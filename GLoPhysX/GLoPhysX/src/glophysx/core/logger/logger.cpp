#include "gxpch.h"

#include "logger.h"

namespace GLOPHYSX {

	Shared<spdlog::logger> Logger::s_core_logger;
	Shared<spdlog::logger> Logger::s_client_logger;

	void Logger::Init()
	{
		std::vector<spdlog::sink_ptr> sinks;

		sinks.emplace_back(MakeShared<spdlog::sinks::stdout_color_sink_mt>());
		sinks[0]->set_pattern("%^[%T] %n: %v%$");

		s_core_logger = MakeShared<spdlog::logger>(CORE_LOGGER_NAME, sinks.begin(), sinks.end());
		s_core_logger->set_level(spdlog::level::trace);
		s_core_logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_core_logger);

		s_client_logger = MakeShared<spdlog::logger>(CLIENT_LOGGER_NAME, sinks.begin(), sinks.end());
		s_client_logger->set_level(spdlog::level::trace);
		s_client_logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_client_logger);
	}

	void Logger::Shutdown()
	{
		spdlog::shutdown();
	}

	Shared<spdlog::logger>& Logger::GetCoreLogger()
	{
		return s_core_logger;
	}

	Shared<spdlog::logger>& Logger::GetClientLogger()
	{
		return s_client_logger;
	}
}
