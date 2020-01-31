#ifndef BIA_THREAD_UNIQUE_LOCK_HPP_
#define BIA_THREAD_UNIQUE_LOCK_HPP_

#include "config.hpp"
#include "lock_behavior.hpp"

#if defined(BIA_THREAD_BACKEND_STD)
#	include <mutex>
#endif

namespace bia {
namespace thread {

#if defined(BIA_THREAD_BACKEND_STD)
template<typename Mutex>
using unique_lock = std::unique_lock<Mutex>;
#elif defined(BIA_THREAD_BACKEND_NONE)
template<typename Mutex>
class unique_lock
{
public:
	unique_lock(Mutex&, try_to_lock_tag) noexcept
	{}
};
#endif

} // namespace thread
} // namespace bia

#endif