#pragma once

#include <condition_variable>
#include <cstddef>
#include <mutex>

namespace bia {
namespace thread {

/*
 A single use barrier. Barriers are used to synchronize specific points between multiple threads.
*/
class barrier
{
public:
	/*
	 Constructor.

	 @param thread_count is the amount of initial threads
	*/
	explicit barrier(std::size_t thread_count)
	{
		arrive_count	   = 0;
		this->thread_count = thread_count;
	}
	void arrive_and_wait()
	{
		std::unique_lock<std::mutex> lock(mutex);

		if (++arrive_count >= thread_count) {
			halter.notify_all();
		} else {
			halter.wait(lock, [this] { return arrive_count >= thread_count; });
		}
	}

private:
	std::mutex mutex;
	std::condition_variable halter;
	std::size_t arrive_count;
	std::size_t thread_count;
};

} // namespace thread
} // namespace bia