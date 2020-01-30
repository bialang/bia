#include "log/log.hpp"

namespace bia {
namespace log {

std::shared_ptr<spdlog::logger> get_default_logger() noexcept
{
#if defined(BIA_LOG_ENABLE_LOGGING)
	static std::shared_ptr<spdlog::logger> logger([] {
		auto logger = spdlog::stdout_color_mt(BIA_LOG_NAME);

		logger->set_pattern(BIA_LOG_PATTERN);

		return logger;
	}());

	return logger;
#else
	return nullptr;
#endif
}

} // namespace log
} // namespace bia