#include <thread/config.hpp>
#include <thread/thread.hpp>
#include <utility>

#ifdef BIA_THREAD_BACKEND_STD
#	include <thread>
#endif // BIA_THREAD_BACKEND_STD

namespace bia {
namespace thread {

struct thread::impl
{
	bool interrupted;
	bool alive;
	bool started;
	bool daemon;
	std::function<void()> target;
#if defined(BIA_THREAD_BACKEND_STD)
	std::thread t;
#endif

	impl(std::function<void()>&& target) : target(std::move(target))
	{
		interrupted = false;
		alive = false;
		started = false;
		daemon = false;
	}
};

thread::thread(std::function<void()> target) : pimpl(new impl(std::move(target)))
{}

thread::~thread()
{}


void thread::join()
{
#if defined(BIA_THREAD_BACKEND_STD)
	pimpl->t.join();
#endif
}

void thread::start()
{
	//todo: lock
	if (pimpl->started) {
		throw;
	}

	pimpl->alive = true;
	pimpl->started = true;

#if defined(BIA_THREAD_BACKEND_STD)
	pimpl->t = std::thread(pimpl->target);

	if (pimpl->daemon) {
		pimpl->t.detach();
	}
#endif
}

void thread::interrupt()
{
	if (pimpl->alive) {
		pimpl->interrupted = true;
	}
}

void thread::daemon(bool daemon)
{
	pimpl->daemon = daemon;
}

void thread::yield()
{
#if defined(BIA_THREAD_BACKEND_STD)
	std::this_thread::yield();
#endif
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
} // namespace bia