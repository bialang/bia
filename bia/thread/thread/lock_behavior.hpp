#ifndef BIA_THREAD_LOCK_BEHAVIOR_HPP_
#define BIA_THREAD_LOCK_BEHAVIOR_HPP_

#include "config.hpp"

#if defined(BIA_THREAD_BACKEND_STD)
#	include <mutex>
#endif

namespace bia {
namespace thread {

#if defined(BIA_THREAD_BACKEND_STD)
using try_to_lock_tag      = std::try_to_lock_t;
constexpr auto try_to_lock = std::try_to_lock;
#elif defined(BIA_THREAD_BACKEND_NONE)
struct try_to_lock_tag
{
	explicit try_to_lock_tag() = default;
};

constexpr try_to_lock_tag try_to_lock{};
#endif

} // namespace thread
} // namespace bia

#endif