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
 * @tparam Type The type of the object.
*/
template<typename Type>
class share
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @tparam Arguments The arguments needed to create the underlying object.
	 *
	 * @param _arguments The arguments.
	 *
	 * @throws See machine::memory::allocator::construct().
	*/
	template<typename... Arguments>
	share(Arguments &&... _arguments)
	{
		_data = machine::machine_context::active_allocator()->construct<data>(Type(std::forward<Arguments>(_arguments)...)).first;
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @param _copy The copy.
	*/
	share(const share & _copy) noexcept
	{
		_data = _copy._data;
		++_data->ref_counter;
	}
	share(share && _move) = delete;
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
			machine::machine_context::active_allocator()->destroy(machine::memory::allocation<data>(_data, sizeof(data)));
		}
	}
	/**
	 * Checks this share has only one owner.
	 *
	 * @since 3.66.135.746
	 * @date 5-Aug-18
	 *
	 * @return true if this share has only one owner, otherwise false.
	*/
	bool only_owner() const noexcept
	{
		return _data->ref_counter == 1;
	}
	/**
	 * Returns the referred object.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @return The object.
	*/
	Type & get() noexcept
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
	const Type & get() const noexcept
	{
		return _data->object;
	}

private:
	struct data
	{
		/** The referenced object. */
		Type object;
		/** The reference counter. */
		size_t ref_counter;

		data(Type && _object) : object(std::forward<Type>(_object))
		{
			ref_counter = 1;
		}
	} *_data;
};

}
}
