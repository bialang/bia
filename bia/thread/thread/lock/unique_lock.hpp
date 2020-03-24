#ifndef BIA_THREAD_LOCK_UNIQUE_LOCK_HPP_
#define BIA_THREAD_LOCK_UNIQUE_LOCK_HPP_

#include "../config.hpp"
#include "lock_behavior.hpp"

#if BIA_THREAD_BACKEND_STD
#	include <mutex>
#endif

namespace bia {
namespace thread {
namespace lock {

#if BIA_THREAD_BACKEND_STD
template<typename Mutex>
using unique_lock = std::unique_lock<Mutex>;
#elif BIA_THREAD_BACKEND_NONE
template<typename Mutex>
class unique_lock
{
public:
	unique_lock(Mutex&) noexcept
	{}
	unique_lock(Mutex&, try_to_lock_tag) noexcept
	{}
	unique_lock(unique_lock&& move) = default;
	operator bool() const noexcept
	{
		return true;
	}
	unique_lock& operator=(unique_lock&& move) = default;
};
#endif

} // namespace lock
} // namespace thread
} // namespace bia

#endif