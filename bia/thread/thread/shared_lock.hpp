#pragma once

namespace bia {
namespace thread {

template<typename Mutex>
class shared_lock
{
public:
	shared_lock(Mutex& mutex) : mutex(mutex)
	{
		mutex.lock_shared();
	}
	~shared_lock()
	{
		mutex.unlock_shared();
	}

private:
	Mutex& mutex;
};

} // namespace thread
} // namespace bia