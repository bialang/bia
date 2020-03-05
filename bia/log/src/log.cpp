#include "log/log.hpp"

#if defined(BIA_LOG_ENABLE_LOGGING)
#include <spdlog/sinks/stdout_color_sinks.h>

namespace bia {
namespace log {

std::shared_ptr<spdlog::logger> get_default_logger() noexcept
{
	static std::shared_ptr<spdlog::logger> logger([] {
		auto logger = spdlog::stdout_color_mt(BIA_LOG_NAME);

		logger->set_pattern(BIA_LOG_PATTERN);
		logger->set_level(spdlog::level::trace);

		return logger;
	}());

	return logger;
}

} // namespace log
} // namespace bia

#endif