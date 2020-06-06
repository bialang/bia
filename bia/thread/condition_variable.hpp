#ifndef BIA_THREAD_CONDITION_VARIABLE_HPP_
#define BIA_THREAD_CONDITION_VARIABLE_HPP_

#include "config.hpp"

#if defined(BIA_THREAD_BACKEND_STD)
#	include <condition_variable>
#elif defined(BIA_THREAD_BACKEND_NONE)
#	include <chrono>
#	include <bia/exception/implementation_error.hpp>

#	if defined(BIA_THREAD_SLEEP_INCLUDE)
#		include BIA_THREAD_SLEEP_INCLUDE
#	endif
#endif

namespace bia {
namespace thread {

#if defined(BIA_THREAD_BACKEND_STD)
using condition_variable     = std::condition_variable;
using condition_variable_any = std::condition_variable_any;
#elif defined(BIA_THREAD_BACKEND_NONE)
class condition_variable
{
public:
	template<typename Lock, typename Predicate>
	void wait(Lock&, Predicate&& predicate)
	{
		if (!predicate()) {
			BIA_IMPLEMENTATION_ERROR("cannot wait indefinitely; aborting");
		}
	}
	template<typename Lock, typename Rep, typename Period, typename Predicate>
	void wait_for(Lock&, std::chrono::duration<Rep, Period> time, Predicate&& predicate)
	{
		if (!predicate()) {
			BIA_THREAD_SLEEP_FUNCITON(time);
		}
	}
	void notify_one() noexcept
	{}
	void notify_all() noexcept
	{}
};

using condition_variable_any = condition_variable;
#endif

} // namespace thread
} // namespace bia

#endif
