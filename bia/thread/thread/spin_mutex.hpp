#ifndef BIA_THREAD_SPING_MUTEX_HPP_
#define BIA_THREAD_SPING_MUTEX_HPP_

#include "config.hpp"

#if defined(BIA_THREAD_BACKEND_STD)
#	include <atomic>
#endif

namespace bia {
namespace thread {

/**
 * A simple mutex which uses the std::atomic_flag for simple locking. This mutex satisfies the requirements of C++
 * `Mutex`.
 */
class spin_mutex
{
public:
	spin_mutex()                       = default;
	spin_mutex(const spin_mutex& copy) = delete;
	spin_mutex(spin_mutex&& move)      = delete;
	/**
	 * Locks the mutex. If the mutex is already locked by another thread this method will block until it acquires the
	 * mutex.
	 */
	void lock() noexcept
	{
#if defined(BIA_THREAD_BACKEND_STD)
		while (_flag.test_and_set(std::memory_order_acquire))
			;
#endif
	}
	/**
	 * Tries to lock the mutex. If the mutex is already locked by another thread this method will return `false`.
	 *
	 * @returns `true` if the mutex was successfully locked, otherwise `false`
	 */
	bool try_lock() noexcept
	{
#if defined(BIA_THREAD_BACKEND_STD)
		return !_flag.test_and_set(std::memory_order_acquire);
#elif defined(BIA_THREAD_BACKEND_NONE)
		return true;
#endif
	}
	/**
	 * Unlocks the mutex.
	 */
	void unlock() noexcept
	{
#if defined(BIA_THREAD_BACKEND_STD)
		_flag.clear(std::memory_order_release);
#endif
	}

private:
#if defined(BIA_THREAD_BACKEND_STD)
	std::atomic_flag _flag = ATOMIC_FLAG_INIT;
#endif
};

} // namespace thread
} // namespace bia

#endif