#ifndef BIA_THREAD_SHARED_SPIN_MUTEX_HPP_
#define BIA_THREAD_SHARED_SPIN_MUTEX_HPP_

#include "config.hpp"

#if defined(BIA_THREAD_BACKEND_STD)
#	include <atomic>

#endif

namespace bia {
namespace thread {

class shared_spin_mutex
{
public:
	shared_spin_mutex() noexcept
	{}
	void lock() noexcept
	{
#if defined(BIA_THREAD_BACKEND_STD)
		// acquire unique lock
		while (!unique.exchange(true, std::memory_order_acquire))
			;

		// wait until all shared locks are released
		while (shared_counter.load(std::memory_order_acquire) > 0)
			;
#endif
	}
	void unlock() noexcept
	{
#if defined(BIA_THREAD_BACKEND_STD)
		unique.store(false, std::memory_order_release);
#endif
	}
	bool try_lock() noexcept
	{
#if defined(BIA_THREAD_BACKEND_STD)
		// already locked
		if (!unique.exchange(true, std::memory_order_acquire)) {
			return false;
		} // there are still shared locks
		else if (shared_counter.load(std::memory_order_acquire) > 0) {
			unique.store(false, std::memory_order_release);

			return false;
		}
#endif

		return true;
	}
	void lock_shared() noexcept
	{
#if defined(BIA_THREAD_BACKEND_STD)
		while (true) {
			// waits while locked
			while (unique.load(std::memory_order_acquire))
				;

			// increment shared counter
			shared_counter.fetch_add(1, std::memory_order_release);

			// try again if the unique lock was acquired
			if (unique.load(std::memory_order_acquire)) {
				shared_counter.fetch_sub(1, std::memory_order_release);
			} // successfully locked
			else {
				break;
			}
		}
#endif
	}
	void unlock_shared() noexcept
	{
#if defined(BIA_THREAD_BACKEND_STD)
		shared_counter.fetch_sub(1, std::memory_order_release);
#endif
	}
	bool try_lock_shared() noexcept
	{
#if defined(BIA_THREAD_BACKEND_STD)
		shared_counter.fetch_add(1, std::memory_order_release);

		// there is already an unique lock
		if (unique.load(std::memory_order_acquire)) {
			shared_counter.fetch_sub(1, std::memory_order_release);

			return false;
		}
#endif

		return true;
	}

private:
#if defined(BIA_THREAD_BACKEND_STD)
	std::atomic_bool unique;
	std::atomic_size_t shared_counter;
#endif
};

} // namespace thread
} // namespace bia

#endif