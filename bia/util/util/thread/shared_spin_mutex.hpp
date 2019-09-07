#pragma once

#include <atomic>

namespace bia {
namespace util {
namespace thread {

class shared_spin_mutex
{
public:
	void lock() noexcept
	{
		while (!unique.exchange(true, std::memory_order_acquire))
			;

		while (shared_counter.load(std::memory_order_acquire) > 0)
			;
	}
	void unlock() noexcept
	{
		unique.store(false, std::memory_order_release);
	}
	bool try_lock() noexcept
	{
		if (!unique.exchange(true, std::memory_order_acquire)) {
			return false;
		} else if (shared_counter.load(std::memory_order_acquire) > 0) {
			unique.store(false, std::memory_order_release);

			return false;
		}

		return true;
	}
	void lock_shared() noexcept
	{
		while (true) {
			while (unique.load(std::memory_order_acquire))
				;

			shared_counter.fetch_add(1, std::memory_order_acquire);

			if (unique.load(std::memory_order_acquire)) {
				shared_counter.fetch_sub(1, std::memory_order_release);
			} else {
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
		shared_counter.fetch_add(1, std::memory_order_acquire);

		if (unique.load(std::memory_order_acquire)) {
			shared_counter.fetch_sub(1, std::memory_order_release);
		} else {
			break;
		}
	}

private:
	std::atomic_bool unique;
	std::atomic_size_t shared_counter;
};

} // namespace thread
} // namespace util
} // namespace bia