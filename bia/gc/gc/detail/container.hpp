#ifndef BIA_GC_DETAIL_CONTAINER_HPP_
#define BIA_GC_DETAIL_CONTAINER_HPP_

#include "../memory/allocator.hpp"
#include "../memory/std_allocator.hpp"

#include <log/log.hpp>
#include <thread/lock/spin_mutex.hpp>
#include <thread/lock/unique_lock.hpp>
#include <unordered_set>
#include <util/gsl.hpp>

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
		token(token&& move) noexcept
		{
			std::swap(_container, move._container);
		}
		~token()
		{
			end_operation();
		}
		void end_operation()
		{
			if (_container) {
				BIA_LOG(DEBUG, "ending operation");

				thread::lock::unique_lock<thread::lock::spin_mutex> lock(_container->_mutex);

				_container->_operation_active = false;

				// merge backlist with main list
				_container->_main.insert(_container->_back.begin(), _container->_back.end());
				_container->_back.clear();

				_container = nullptr;
			}
		}
		bool valid() const noexcept
		{
			return _container;
		}
		typename container::container_type::iterator begin()
		{
			BIA_EXPECTS(valid());

			return _container->_main.begin();
		}
		typename container::container_type::iterator end()
		{
			BIA_EXPECTS(valid());

			return _container->_main.end();
		}
		typename container::container_type::iterator erase(typename container::container_type::iterator it)
		{
			BIA_EXPECTS(valid());

			return _container->_main.erase(it);
		}
		token& operator=(token&& move)
		{
			end_operation();

			std::swap(_container, move._container);
		}

	private:
		friend container;

		container* _container = nullptr;

		token(util::not_null<container*> container) noexcept
		{
			_container = container.get();
		}
	};

	container(util::not_null<std::shared_ptr<memory::allocator>> allocator)
	    : _main(allocator), _back(allocator)
	{}
	token begin_operation()
	{
		thread::lock::unique_lock<thread::lock::spin_mutex> lock(_mutex);

		BIA_EXPECTS(!_operation_active);

		_operation_active = true;

		return { this };
	}
	void add(T element)
	{
		thread::lock::unique_lock<thread::lock::spin_mutex> lock(_mutex);

		if (_operation_active) {
			_back.insert(std::move(element));
		} else {
			_main.insert(std::move(element));
		}
	}
	void remove(const T& element)
	{
		thread::lock::unique_lock<thread::lock::spin_mutex> lock(_mutex);

		BIA_LOG(TRACE, "removing element from container");

		if (!_main.erase(element)) {
			BIA_EXPECTS(_back.erase(element) > 0);
		}
	}

private:
	bool _operation_active = false;
	/** the main container type */
	container_type _main;
	/** the main container during an active operation */
	container_type _back;
	thread::lock::spin_mutex _mutex;
};

} // namespace detail
} // namespace gc
} // namespace bia

#endif