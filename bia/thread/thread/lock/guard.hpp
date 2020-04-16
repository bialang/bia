#ifndef BIA_THREAD_LOCK_GUARD_HPP_
#define BIA_THREAD_LOCK_GUARD_HPP_

#include <utility>

namespace bia {
namespace thread {
namespace lock {

template<typename BasicLockable>
class guard
{
public:
	guard(BasicLockable& lock)
	{
		_lock = &lock;

		_lock->lock();
	}
	guard(guard&& move) noexcept
	{
		std::swap(_lock, move._lock);
	}
	~guard()
	{
		if (_lock) {
			_lock->unlock();
		}
	}
	guard& operator=(guard&& move)
	{
		if (_lock) {
			_lock->unlock();
		}

		_lock      = move._lock;
		move._lock = nullptr;

		return *this;
	}

private:
	BasicLockable* _lock = nullptr;
};

} // namespace lock
} // namespace thread
} // namespace bia

#endif