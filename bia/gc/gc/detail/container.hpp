#ifndef BIA_GC_DETAIL_CONTAINER_HPP_
#define BIA_GC_DETAIL_CONTAINER_HPP_

#include "../std_memory_allocator.hpp"

#include <thread/hybrid_mutex.hpp>
#include <thread/shared_lock.hpp>
#include <thread/shared_spin_mutex.hpp>
#include <thread/spin_mutex.hpp>
#include <unordered_set>

namespace bia {
namespace gc {
namespace detail {

template<typename T>
class container
{
public:
	class token
	{
	public:
		token(const token& copy) = delete;
		token(tokem&& move) noexcept
		{
			_container      = move._container;
			move._container = nullptr;
		}
		~token()
		{
			end_operation();
		}
		void end_operation()
		{
			if (_container) {
				// merge backlist with main list

				_container->_mutex.unlock();

				_container = nullptr;
			}
		}
		container::container_type::iterator begin()
		{}
		container::container_type::iterator end()
		{}
		container::container_type::iterator erase(container::container_type::iterator it)
		{}

	private:
		container* _container;

		token(container* container) noexcept
		{
			_container = container;

			_container->_main.lock();
		}
	};

	token begin_operation()
	{
		return { this };
	}
	void add(T element)
	{
		thread::shared_lock<thread::hybrid_mutex> lock(_mutex, thread::try_lock);

		// add directly to the main list
		if (lock) {
			thread::unique_lock<thread::spin_mutex> _(_main_mutex);

			_main.insert(std::move(element));
		} // add to back list
		else {
			thread::unique_lock<thread::spin_mutex> _(_back_mutex);

			_back.insert(std::move(element));
		}
	}
	void remove(const T& element)
	{}

private:
	typedef std::unordered_set<T, std::hash<T>, std::equal_to<T>, std_memory_allocator<T>> container_type;

	container_type _main;
	thread::hybrid_mutex _mutex;
	thread::spin_mutex _main_mutex;
	container_type _back;
	thread::spin_mutex _back_mutex;
};

} // namespace detail
} // namespace gc
} // namespace bia

#endif