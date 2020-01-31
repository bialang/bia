#ifndef BIA_THREAD_LOCK_BEHAVIOR_HPP_
#define BIA_THREAD_LOCK_BEHAVIOR_HPP_

#include "config.hpp"

#if defined(BIA_THREAD_BACKEND_STD)
#	include <thread>
#endif

namespace bia {
namespace thread {

#if defined(BIA_THREAD_BACKEND_STD)
constexpr auto try_to_lock = std::try_to_lock;
#elif defined(BIA_THREAD_BACKEND_NONE)
typedef struct
{
} try_to_lock_type;

constexpr try_to_lock_type try_to_lock{};
#endif

} // namespace thread
} // namespace bia

#endif