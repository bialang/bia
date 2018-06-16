#pragma once

#include <atomic>
#include <utility>

#include "allocator.hpp"


namespace bia
{
namespace utility
{


template<typename _Ty>
class share
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @tparam _Args The arguments needed to create the underlying object.
	 *
	 * @param [in] _allocator The memory allocator.
	 * @param _args The arguments.
	 *
	 * @throws See machine::memory::allocator::construct().
	*/
	template<typename... _Args>
	share(machine::memory::allocator * _allocator, _Args &&... _args)
	{
		_data = _allocator->construct<data>(_Ty(std::forward<_Args>(_args)...), _allocator).first;
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @param _copy The copy.
	*/
	share(const share<_Ty> & _copy) noexcept
	{
		_data = _copy._data;
		_data->ref_counter.fetch_add(1, std::memory_order_relaxed);
	}
	share(share<_Ty>&&) = delete;
	/**
	 * Destructor.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @throws See machine::memory::allocator::destroy().
	*/
	~share()
	{
		if (_data->ref_counter.fetch_sub(1, std::memory_order_release) == 1) {
			std::atomic_thread_fence(std::memory_order_acquire);

			_data->allocator->destroy(machine::memory::allocator::allocation<data>(_data, sizeof(data)));
		}
	}
	/**
	 * Returns the referred object.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @return The object.
	*/
	_Ty & get() noexcept
	{
		return _data->object;
	}
	/**
	 * Returns the referred object.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @return The object.
	*/
	const _Ty & get() const noexcept
	{
		return _data->object;
	}
	/**
	 * Returns the allocator.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @return The allocator.
	*/
	machine::memory::allocator * get_allocator() noexcept
	{
		return _data->allocator;
	}

private:
	struct data
	{
		/** The referenced object. */
		_Ty object;
		/** The reference counter. */
		std::atomic_size_t ref_counter;
		/** The memory allocator. */
		machine::memory::allocator * allocator;

		data(_Ty && _object, machine::memory::allocator * _allocator) : object(std::forward<_Ty>(_object)), ref_counter(1)
		{
			allocator = _allocator;
		}
	} *_data;
};

}
}