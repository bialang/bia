#ifndef BIA_LOG_LOG_HPP_
#define BIA_LOG_LOG_HPP_

#include "config.hpp"

#include <memory>

#if BIA_LOG_ENABLE
#	include <spdlog/spdlog.h>
#	include <spdlog/fmt/fmt.h>
#	include <chrono>
#	include <type_traits>

#	define BIA_LOG(level, ...) SPDLOG_LOGGER_##level(bia::log::get_default_logger(), __VA_ARGS__)

namespace fmt {

template<typename Rep, typename Period>
struct formatter<std::chrono::duration<Rep, Period>>
{
	auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
	{
		return ctx.begin();
	}

	template<typename Context>
	auto format(const std::chrono::duration<Rep, Period>& duration, Context& context) -> decltype(context.out())
	{
		const char* unit = "?";
		if (std::is_same<Period, std::nano>::value) {
			unit = "ns";
		} else if (std::is_same<Period, std::micro>::value) {
			unit = "µs";
		} else if (std::is_same<Period, std::milli>::value) {
			unit = "ms";
		}
		return format_to(context.out(), "{}{}", duration.count(), unit);
	}
};

} // namespace fmt
#else
#	define BIA_LOG(...) ((void) 0)
#endif

#define BIA_LOG_ERROR(level, error)                                                                          \
	BIA_LOG(level, "exception caught ({}, {}:{}): {}", error.name(), error.filename(), error.line(),           \
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
