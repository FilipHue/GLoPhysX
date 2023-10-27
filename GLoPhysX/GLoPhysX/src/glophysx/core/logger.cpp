#include "logger.h"

namespace GLOPHYSX {

	std::shared_ptr<spdlog::logger> Logger::s_core_logger;
	std::shared_ptr<spdlog::logger> Logger::s_client_logger;

	void Logger::Init()
	{
		std::vector<spdlog::sink_ptr> sinks;

		sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		sinks[0]->set_pattern("%^[%T] %n: %v%$");

		s_core_logger = std::make_shared<spdlog::logger>(CORE_LOGGER_NAME, sinks.begin(), sinks.end());
		s_core_logger->set_level(spdlog::level::trace);
		s_core_logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_core_logger);

		s_client_logger = std::make_shared<spdlog::logger>(CLIENT_LOGGER_NAME, sinks.begin(), sinks.end());
		s_client_logger->set_level(spdlog::level::trace);
		s_client_logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(s_client_logger);
	}
	void Logger::Shutdown()
	{
		spdlog::shutdown();
	}
}

