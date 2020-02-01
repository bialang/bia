#ifndef BIA_THREAD_SHARED_LOCK_HPP_
#define BIA_THREAD_SHARED_LOCK_HPP_

#include "lock_behavior.hpp"

namespace bia {
namespace thread {

template<typename Mutex>
class shared_lock
{
public:
	shared_lock(Mutex& mutex) : _mutex(mutex)
	{
		_mutex.lock_shared();

		_locked = true;
	}
	shared_lock(Mutex& mutex, try_to_lock_tag) : _mutex(mutex)
	{
		_locked = _mutex.try_lock();
	}
	~shared_lock()
	{
		if (_locked) {
			_mutex.unlock_shared();
		}
	}
	operator bool() const noexcept
	{
		return _locked;
	}

private:
	Mutex& _mutex;
	bool _locked;
};

} // namespace thread
} // namespace bia

#endif