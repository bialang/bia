#include <chrono>
#include <exception/interrupt_exception.hpp>
#include <thread/config.hpp>
#include <thread/hybrid_mutex.hpp>
#include <thread/thread.hpp>
#include <unordered_map>
#include <utility>

#ifdef BIA_THREAD_BACKEND_STD
#	include <thread>
#	include <condition_variable>
#endif // BIA_THREAD_BACKEND_STD

namespace bia {
namespace thread {

struct thread::impl
{
	volatile bool interrupted;
	bool alive;
	bool started;
	bool daemon;
	std::function<void()> target;
	hybrid_mutex mutex;
	std::exception_ptr exptr;
#if defined(BIA_THREAD_BACKEND_STD)
	std::thread t;
	std::condition_variable_any cv;
	static std::unordered_map<std::thread::id, thread> threads;
#endif

	impl(std::function<void()>&& target) : mutex(100), target(std::move(target))
	{
		interrupted = false;
		alive		= false;
		started		= false;
		daemon		= false;
	}
};

#if defined(BIA_THREAD_BACKEND_STD)
std::unordered_map<std::thread::id, thread> thread::impl::threads;
#endif

thread::thread(std::function<void()> target) : pimpl(new impl(std::move(target)))
{}

thread::~thread()
{}

void thread::yield()
{
#if defined(BIA_THREAD_BACKEND_STD)
	std::this_thread::yield();
#endif
}

void thread::sleep(std::uintmax_t duration)
{
	auto t = current_thread();

	std::unique_lock<decltype(impl::mutex)> lock(t.pimpl->mutex);

	// sleep was interrupted
	if (t.pimpl->cv.wait_for(lock, std::chrono::duration<std::uintmax_t, std::milli>(duration),
							 [&t] { return t.pimpl->interrupted; })) {
		// consume and throw
		t.pimpl->interrupted = false;

		BIA_THROW(exception::interrupt_exception, u"current sleep was interrupted");
	}
}

thread thread::current_thread()
{
#if defined(BIA_THREAD_BACKEND_STD)
	auto result = impl::threads.find(std::this_thread::get_id());

	// create thread
	if (result == impl::threads.end()) {
	}

	return result->second;
#endif
}

void thread::join()
{
	std::unique_lock<decltype(impl::mutex)> lock(pimpl->mutex);

#if defined(BIA_THREAD_BACKEND_STD)
	pimpl->t.join();
#endif

	// an exception occurred
	if (pimpl->exptr) {
		std::rethrow_exception(pimpl->exptr);
	}
}

void thread::start()
{
	std::unique_lock<decltype(impl::mutex)> lock(pimpl->mutex);

	if (pimpl->started) {
		throw;
	}

	pimpl->alive   = true;
	pimpl->started = true;

	auto target = [this] {
		try {
			pimpl->target();
		} catch (...) {
			pimpl->exptr = std::current_exception();
		}

		pimpl->alive = false;
	};

#if defined(BIA_THREAD_BACKEND_STD)
	pimpl->t = std::thread(target);

	impl::threads.insert({ std::this_thread::get_id(), *this });

	// make daemon
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

	// thread was already started
	if (pimpl->started) {
	}

	pimpl->daemon = daemon;
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