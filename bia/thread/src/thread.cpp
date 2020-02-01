#include "thread/condition_variable.hpp"
#include "thread/mutex.hpp"
#include "thread/thread.hpp"

#include <exception/interrupt_error.hpp>
#include <exception/unsupported_error.hpp>
#include <exception>
#include <log/log.hpp>
#include <util/gsl.hpp>

#if defined(BIA_THREAD_BACKEND_STD)
#	include <thread>
#elif defined(BIA_THREAD_BACKEND_NONE)
#	if defined(BIA_THREAD_SLEEP_INCLUDE)
#		include BIA_THREAD_SLEEP_INCLUDE
#	endif
#endif

namespace bia {
namespace thread {

struct thread::impl
{
	bool valid;
#if defined(BIA_THREAD_BACKEND_STD)
	std::thread thread_backend;
#endif

	impl(std::function<void()> target)
	{
		if (target) {
			valid = true;

#if defined(BIA_THREAD_BACKEND_STD)
			thread_backend = std::thread(std::move(target));

			BIA_LOG(INFO, "new thread launched");
#elif defined(BIA_THREAD_BACKEND_NONE)
			BIA_LOG(CRITICAL, "tried to launch thread; operation unsupported");

			BIA_THROW(exception::unsupported_error, "threads are not supported");
#endif
		} else {
			valid = false;
		}
	}
};

thread::thread(std::function<void()> target) : _pimpl(new impl(std::move(target)))
{}

thread::~thread()
{}

void thread::yield()
{
#if defined(BIA_THREAD_BACKEND_STD)
	std::this_thread::yield();
#endif
}

void thread::sleep(std::chrono::milliseconds duration)
{
#if defined(BIA_THREAD_BACKEND_STD)
	std::this_thread::sleep_for(duration);
#elif defined(BIA_THREAD_BACKEND_NONE)
	BIA_THREAD_SLEEP_FUNCTION(duration);
#endif
}

void thread::join()
{
#if defined(BIA_THREAD_BACKEND_STD)
	BIA_EXPECTS(valid());
#endif
}

bool thread::valid() const noexcept
{
#if defined(BIA_THREAD_BACKEND_STD)
	return _pimpl->valid;
#elif defined(BIA_THREAD_BACKEND_NONE)
	return false;
#endif
}

bool thread::supported() noexcept
{
#if defined(BIA_THREAD_BACKEND_STD)
	return true;
#elif defined(BIA_THREAD_BACKEND_NONE)
	return false;
#endif
}

} // namespace thread
} // namespace bia