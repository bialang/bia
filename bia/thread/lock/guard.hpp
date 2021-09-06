#ifndef BIA_THREAD_LOCK_GUARD_HPP_
#define BIA_THREAD_LOCK_GUARD_HPP_

#include <utility>

namespace bia {
namespace thread {
namespace lock {

template<typename BasicLockable>
class Guard
{
public:
	Guard(BasicLockable& lock)
	{
		_lock = &lock;
		_lock->lock();
	}
	Guard(Guard&& move) noexcept
	{
		std::swap(_lock, move._lock);
	}
	~Guard() noexcept
	{
		if (_lock) {
			_lock->unlock();
		}
	}
	Guard& operator=(Guard&& move)
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
