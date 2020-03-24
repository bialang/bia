#ifndef BIA_THREAD_LOCK_LOCK_BEHAVIOR_HPP_
#define BIA_THREAD_LOCK_LOCK_BEHAVIOR_HPP_

#include "../config.hpp"

#if BIA_THREAD_BACKEND_STD
#	include <mutex>
#endif

namespace bia {
namespace thread {
namespace lock {

#if BIA_THREAD_BACKEND_STD
using try_to_lock_tag      = std::try_to_lock_t;
constexpr auto try_to_lock = std::try_to_lock;
#elif BIA_THREAD_BACKEND_NONE
struct try_to_lock_tag
{
	explicit try_to_lock_tag() = default;
};

constexpr try_to_lock_tag try_to_lock{};
#endif

} // namespace lock
} // namespace thread
} // namespace bia

#endif