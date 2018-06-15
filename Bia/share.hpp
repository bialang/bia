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
	share() noexcept
	{
		_data = nullptr;
	}
	share(const share<_Ty>&) = delete;
	share(share<_Ty> && _move) noexcept
	{
		_data = _move._data;
		_move._data = nullptr;
	}

	template<typename _Deleter>
	void dereference(machine::memory::allocator * _allocator, _Deleter && _deleter)
	{
		// Delete
		if (_data && _data->ref_counter.fetch_sub(1, std::memory_order_release) == 1) {
			std::atomic_thread_fence(std::memory_order_acquire);

			_deleter(_data->object);
			_allocator->destroy_blocks(machine::memory::allocator::allocation<std::atomic_size_t>(_data, sizeof(data)));
			_data = nullptr;
		}
	}
	void reference(_Ty && _object, machine::memory::allocator * _allocator)
	{
		_data = _allocator->construct_blocks<data>(1, std::forward<_Ty>(_object)).first;
	}
	void reference(const share<_Ty> & _reference)
	{
		_data = _reference._data;
		_data->ref_counter.fetch_add(1, std::memory_order_relaxed);
	}
	_Ty & get()
	{
		return _data->object;
	}
	const _Ty & get() const
	{
		return _data->object;
	}
	share<_Ty> & operator=(share<_Ty> && _right) noexcept
	{
		_data = _right._data;
		_right._data = nullptr;

		return *this;
	}

private:
	struct data
	{
		/** The referenced object. */
		_Ty object;
		/** The reference counter. */
		std::atomic_size_t ref_counter;

		data(_Ty && _object) : object(std::forward<_Ty>(_object)), ref_counter(1)
		{
		}
	} *_data;
};

}
}