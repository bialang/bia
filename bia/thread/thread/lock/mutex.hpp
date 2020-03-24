#ifndef BIA_THREAD_LOCK_MUTEX_HPP_
#define BIA_THREAD_LOCK_MUTEX_HPP_

#include "../config.hpp"

#if BIA_THREAD_BACKEND_STD
#	include <mutex>
#endif

namespace bia {
namespace thread {
namespace lock {

#if BIA_THREAD_BACKEND_STD
using mutex = std::mutex;
#elif BIA_THREAD_BACKEND_NONE
class mutex
{
public:
	void lock() noexcept
	{}
	bool try_lock() noexcept
	{
		return true;
	}
	void unlock() noexcept
	{}
};
#endif

} // namespace lock
} // namespace thread
} // namespace bia

#endif