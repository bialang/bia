#pragma once

#include <atomic>
#include <utility>

#include "allocator.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace utility
{

/**
 * @brief A shared object.
 *
 * A shared object with reference counting in only one thread.
 *
 * @tparam _Ty The type of the object.
*/
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
	 * @param _args The arguments.
	 *
	 * @throws See machine::memory::allocator::construct().
	*/
	template<typename... _Args>
	share(_Args &&... _args)
	{
		_data = machine::machine_context::active_allocator()->construct<data>(_Ty(std::forward<_Args>(_args)...)).first;
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
		++_data->ref_counter;
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
		if (!--_data->ref_counter) {
			machine::machine_context::active_allocator()->destroy(machine::memory::allocator::allocation<data>(_data, sizeof(data)));
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

private:
	struct data
	{
		/** The referenced object. */
		_Ty object;
		/** The reference counter. */
		size_t ref_counter;

		data(_Ty && _object) : object(std::forward<_Ty>(_object))
		{
			ref_counter = 1;
		}
	} *_data;
};

}
}