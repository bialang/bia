#pragma once

#include <cstddef>
#include <mutex>

namespace bia {
namespace thread {

class hybrid_mutex
{
public:
	hybrid_mutex(std::size_t spin_limit) : spin_limit(spin_limit)
	{}
	void lock()
	{
		for (std::size_t i = 0; i < spin_limit; ++i) {
			if (mutex.try_lock()) {
				return;
			}
		}

		mutex.lock();
	}
	bool try_lock()
	{
		return mutex.try_lock();
	}
	void unlock()
	{
		mutex.unlock();
	}

private:
	std::mutex mutex;
	std::size_t const spin_limit;
};

} // namespace thread
} // namespace bia