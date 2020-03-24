#ifndef BIA_THREAD_LOCK_SHARED_LOCK_HPP_
#define BIA_THREAD_LOCK_SHARED_LOCK_HPP_

#include "lock_behavior.hpp"

namespace bia {
namespace thread {
namespace lock {

template<typename Mutex>
class shared_lock
{
public:
	shared_lock(Mutex& mutex)
	{
		mutex.lock_shared();

		_mutex  = &mutex;
		_locked = true;
	}
	shared_lock(Mutex& mutex, try_to_lock_tag)
	{
		_mutex  = &mutex;
		_locked = mutex.try_lock();
	}
	shared_lock(shared_lock&& move) noexcept
	{
		std::swap(_mutex, move._mutex);
		std::swap(_locked, move._locked);
	}
	~shared_lock()
	{
		if (_locked) {
			_mutex->unlock_shared();
		}
	}
	operator bool() const noexcept
	{
		return _locked;
	}
	shared_lock& operator=(shared_lock&& move)
	{
		if (_locked) {
			_mutex->unlock_shared();
		}

		_mutex       = move._mutex;
		_locked      = move._locked;
		move._mutex  = nullptr;
		move._locked = false;
	}

private:
	Mutex* _mutex = nullptr;
	bool _locked  = false;
};

} // namespace lock
} // namespace thread
} // namespace bia

#endif