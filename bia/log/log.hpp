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
		using namespace std::chrono;
		const char* unit;
		double t = duration_cast<nanoseconds>(duration).count();
		if (duration < nanoseconds{ 1000 }) {
			unit = "ns";
		} else if (duration < microseconds{ 1000 }) {
			unit = "µs";
			t /= 1000;
		} else if (duration < milliseconds{ 1000 }) {
			unit = "ms";
			t /= 1000000;
		} else {
			unit = "s";
			t /= 10000000000;
		}
		return format_to(context.out(), "{:.2f} {}", t, unit);
	}
};

} // namespace fmt
#else
#	define BIA_LOG(...) ((void) 0)
#endif

#define BIA_LOG_ERROR(level, error)                                                                          \
	BIA_LOG(level, "Exception caught ({}, {}:{}): {}", error.name(), error.filename(), error.line(),           \
	        error.what())

namespace spdlog {

class logger;

}

namespace bia {
namespace log {

/// Returns Bia's default logger if enabled otherwise `nullptr`.
std::shared_ptr<spdlog::logger> get_default_logger() noexcept;

} // namespace log
} // namespace bia

#endif
