#ifndef BIA_THREAD_MUTEX_HPP_
#define BIA_THREAD_MUTEX_HPP_

#include "config.hpp"

#if defined(BIA_THREAD_BACKEND_STD)
#	include <mutex>
#endif

namespace bia {
namespace thread {

#if defined(BIA_THREAD_BACKEND_STD)
using mutex = std::mutex;
#elif defined(BIA_THREAD_BACKEND_NONE)
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

} // namespace thread
} // namespace bia

#endif