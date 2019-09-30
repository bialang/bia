#include <thread/config.hpp>
#include <thread/thread.hpp>
#include <thread/hybrid_mutex.hpp>
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
	hybrid_mutex mutex;
#if defined(BIA_THREAD_BACKEND_STD)
	std::thread t;
#endif

	impl(std::function<void()>&& target) : mutex(100), target(std::move(target))
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
	std::unique_lock<decltype(impl::mutex)> lock(pimpl->mutex);

#if defined(BIA_THREAD_BACKEND_STD)
	pimpl->t.join();
#endif
}

void thread::start()
{
	std::unique_lock<decltype(impl::mutex)> lock(pimpl->mutex);
	
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
	std::unique_lock<decltype(impl::mutex)> lock(pimpl->mutex);
	
	if (pimpl->alive) {
		pimpl->interrupted = true;
	}
}

void thread::daemon(bool daemon)
{
	std::unique_lock<decltype(impl::mutex)> lock(pimpl->mutex);
	
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
	std::unique_lock<decltype(impl::mutex)> lock(pimpl->mutex);
	
	return pimpl->daemon;
}

bool thread::alive() const noexcept
{
	std::unique_lock<decltype(impl::mutex)> lock(pimpl->mutex);
	
	return pimpl->alive;
}

bool thread::interrupted() const noexcept
{
	std::unique_lock<decltype(impl::mutex)> lock(pimpl->mutex);
	
	return pimpl->interrupted;
}

} // namespace thread
} // namespace bia