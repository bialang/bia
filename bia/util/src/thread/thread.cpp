#include <util/config.hpp>
#include <util/thread/thread.hpp>

#ifdef BIA_THREAD_BACKEND_STD
#	include <thread>
#endif // BIA_THREAD_BACKEND_STD

namespace bia {
namespace util {
namespace thread {

struct thread::impl
{
	bool interrupted;
	bool alive;
	bool started;
	bool daemon;
	std::function<void()> target;
};

thread::thread(std::function<void()> target)
{}

thread::~thread()
{}

void thread::start()
{}

void thread::interrupt()
{}

void thread::daemon(bool daemon)
{
	pimpl->daemon = daemon;
}

void thread::yield()
{
#ifdef BIA_THREAD_BACKEND_STD
	std::this_thread::yield();
#endif // BIA_THREAD_BACKEND_STD
}

bool thread::daemon() const noexcept
{
	return pimpl->daemon;
}

bool thread::alive() const noexcept
{
	return pimpl->alive;
}

bool thread::interrupted() const noexcept
{
	return pimpl->interrupted;
}

} // namespace thread
} // namespace util
} // namespace bia