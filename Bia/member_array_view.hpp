#pragma once

#include <cstdint>
#include <vector>
#include <utility>

#include "member.hpp"
#include "max_member_size.hpp"
#include "undefined_member.hpp"


namespace bia
{
namespace machine
{

class member_array_view
{
public:
	/** The index type. */
	typedef uint32_t index_t;

	/**
	 * Constructor.
	 *
	 * @since 3.79.150.825
	 * @date 4-Apr-19
	 *
	 * @param [in] _array The the member array. Must be at least @a _member_count * @ref framework::max_member_size large.
	 * @param _member_count The amount of member variables.
	*/
	member_array_view(void * _array, size_t _member_count) noexcept
	{
		_begin = static_cast<int8_t*>(_array);
		_end = _begin + _member_count * framework::max_member_size;

		// Initialize
		for (auto i = _begin; i < _end; i += framework::max_member_size) {
			new(i) framework::undefined_member();
		}

		_end -= framework::max_member_size;
	}
	member_array_view(const member_array_view & _copy) = delete;
	member_array_view(member_array_view && _move)
	{
		_begin = _move._begin;
		_end = _move._end;

		_move._begin = nullptr;
		_move._end = nullptr;
	}
	/**
	 * Destructor.
	 *
	 * @since 3.79.150.825
	 * @date 4-Apr-19
	 *
	 * @throws See framework::member::~member().
	*/
	~member_array_view()
	{
		_end += framework::max_member_size;

		// Destroy all members
		for (auto i = _begin; i < _end; i += framework::max_member_size) {
			reinterpret_cast<framework::member*>(i)->~member();
		}
	}
	/**
	 * Returns the nth element from the front.
	 *
	 * @since 3.79.150.825
	 * @date 4-Apr-19
	 *
	 * @param _index The index of the element. Must be within the view.
	 *
	 * @return The member.
	*/
	framework::member * from_front(index_t _index) noexcept
	{
		return reinterpret_cast<framework::member*>(_begin + _index * framework::max_member_size);
	}
	/**
	 * Returns the nth element from the back.
	 *
	 * @since 3.79.150.825
	 * @date 4-Apr-19
	 *
	 * @param _index The index of the element. Must be within the view.
	 *
	 * @return The member.
	*/
	framework::member * from_back(index_t _index) noexcept
	{
		return reinterpret_cast<framework::member*>(_end - _index * framework::max_member_size);
	}
	member_array_view & operator=(const member_array_view & _copy) = delete;
	member_array_view & operator=(member_array_view && _move)
	{
		std::swap(_begin, _move._begin);
		std::swap(_end, _move._end);

		return *this;
	}

private:
	int8_t * _begin;
	int8_t * _end;
};

}
}