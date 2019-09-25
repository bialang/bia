#pragma once

#include <atomic>

namespace bia {
namespace util {
namespace thread {

class shared_spin_mutex
{
public:
	shared_spin_mutex() noexcept : unique(false), shared_counter(0)
	{}
	void lock() noexcept
	{
		// acquire unique lock
		while (!unique.exchange(true, std::memory_order_acquire))
			;

		// wait until all shared locks are released
		while (shared_counter.load(std::memory_order_acquire) > 0)
			;
	}
	void unlock() noexcept
	{
		unique.store(false, std::memory_order_release);
	}
	bool try_lock() noexcept
	{
		// already locked
		if (!unique.exchange(true, std::memory_order_acquire)) {
			return false;
		} // there are still shared locks
		else if (shared_counter.load(std::memory_order_acquire) > 0) {
			unique.store(false, std::memory_order_release);

			return false;
		}

		return true;
	}
	void lock_shared() noexcept
	{
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
	}
	void unlock_shared() noexcept
	{
		shared_counter.fetch_sub(1, std::memory_order_release);
	}
	bool try_lock_shared() noexcept
	{
		shared_counter.fetch_add(1, std::memory_order_release);

		// there is already an unique lock
		if (unique.load(std::memory_order_acquire)) {
			shared_counter.fetch_sub(1, std::memory_order_release);

			return false;
		}

		return true;
	}

private:
	std::atomic_bool unique;
	std::atomic_size_t shared_counter;
};

} // namespace thread
} // namespace util
} // namespace bia