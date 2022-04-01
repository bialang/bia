#include "log.hpp"

#if !BIA_LOG_IS(OFF)
#	include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> bia::log::get_default_logger() noexcept
{
	static std::shared_ptr<spdlog::logger> logger([] {
		auto logger = spdlog::stdout_color_mt(BIA_LOG_NAME);
		logger->set_pattern(BIA_LOG_PATTERN);
		logger->set_level(spdlog::level::trace);
		return logger;
	}());
	return logger;
}

#endif
