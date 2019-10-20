#pragma once

#include <atomic>

namespace bia {
namespace thread {

/*
 A simple mutex which uses the std::atomic_flag for simple locking. This mutex satisfies the requirements of C++
 *Mutex*.
*/
class spin_mutex
{
public:
	spin_mutex()					   = default;
	spin_mutex(const spin_mutex& copy) = delete;
	spin_mutex(spin_mutex&& move)	  = delete;
	/*
	 Locks the mutex. If the mutex is already locked by another thread this method will block until it acquires the
	 mutex.
	*/
	void lock() noexcept
	{
		while (flag.test_and_set(std::memory_order_acquire))
			;
	}
	/*
	 Tries to lock the mutex. If the mutex is already locked by another thread this method will return `false`.

	 @returns `true` if the mutex was successfully locked, otherwise `false`
	*/
	bool try_lock() noexcept
	{
		return !flag.test_and_set(std::memory_order_acquire);
	}
	/*
	 Unlocks the mutex.
	*/
	void unlock() noexcept
	{
		flag.clear(std::memory_order_release);
	}

private:
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

} // namespace thread
} // namespace bia