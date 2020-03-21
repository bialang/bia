#ifndef BIA_GC_DETAIL_CONTAINER_HPP_
#define BIA_GC_DETAIL_CONTAINER_HPP_

#include "../memory/allocator.hpp"
#include "../memory/std_allocator.hpp"

#include <log/log.hpp>
#include <thread/shared_lock.hpp>
#include <thread/shared_spin_mutex.hpp>
#include <thread/spin_mutex.hpp>
#include <thread/unique_lock.hpp>
#include <unordered_set>

namespace bia {
namespace gc {
namespace detail {

template<typename T>
class container
{
public:
	typedef std::unordered_set<T, std::hash<T>, std::equal_to<T>, memory::std_allocator<T>> container_type;

	class token
	{
	public:
		token(const token& copy) = delete;
		token(token&& move) noexcept
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
				BIA_LOG(DEBUG, "ending operation");

				// merge backlist with main list

				_container->_mutex.unlock();

				_container = nullptr;
			}
		}
		typename container::container_type::iterator begin() noexcept
		{
			return _container->_main.begin();
		}
		typename container::container_type::iterator end() noexcept
		{
			return _container->_main.end();
		}
		typename container::container_type::iterator erase(typename container::container_type::iterator it)
		{
			return _container->_main.erase(it);
		}

	private:
		friend container;

		container* _container;

		token(container* container) noexcept
		{
			_container = container;

			_container->_mutex.lock();
		}
	};

	container(util::not_null<std::shared_ptr<memory::allocator>> allocator)
	    : _main(allocator), _back(allocator)
	{}
	token begin_operation()
	{
		return { this };
	}
	void add(T element)
	{
		thread::shared_lock<thread::shared_spin_mutex> lock(_mutex, thread::try_to_lock);

		// add directly to the main list
		if (lock) {
			BIA_LOG(TRACE, "mutex acquired; trying to put element to main container");

			thread::unique_lock<thread::spin_mutex> _(_main_mutex);

			_main.insert(std::move(element));
		} // add to back list
		else {
			BIA_LOG(TRACE, "mutex not acquired; trying to put element to back container");

			thread::unique_lock<thread::spin_mutex> _(_back_mutex);

			_back.insert(std::move(element));
		}
	}
	void remove(const T& element)
	{
		BIA_LOG(TRACE, "removing element from container");
		// todo implement correctly
		_main.erase(element);
	}

private:
	container_type _main;
	thread::shared_spin_mutex _mutex;
	thread::spin_mutex _main_mutex;
	container_type _back;
	thread::spin_mutex _back_mutex;
};

} // namespace detail
} // namespace gc
} // namespace bia

#endif