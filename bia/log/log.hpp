#ifndef BIA_LOG_LOG_HPP_
#define BIA_LOG_LOG_HPP_

#include "config.hpp"

#include <memory>

#if BIA_LOG_ENABLE
#	include <spdlog/spdlog.h>

#	define BIA_LOG(level, ...) SPDLOG_LOGGER_##level(bia::log::get_default_logger(), __VA_ARGS__)
#else
#	define BIA_LOG(...) ((void) 0)
#endif

#define BIA_LOG_ERROR(level, error)                                                                          \
	BIA_LOG(level, "exception caught ({}, {}:{}): {}", error.name(), error.filename(), error.line(),         \
	        error.what())

namespace spdlog {

class logger;

}

namespace bia {
namespace log {

/**
 * Returns the Bia's default logger.
 *
 * @returns the default logger is logging is enabled, otherwise `nullptr`
 */
std::shared_ptr<spdlog::logger> get_default_logger() noexcept;

} // namespace log
} // namespace bia

#endif
