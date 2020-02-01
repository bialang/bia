#pragma once

#include "object_ptr.hpp"

#include <cstddef>
#include <exception/bounds_error.hpp>

namespace bia {
namespace gc {

/**
 * The root array created by the gc where all gc monitored memory originates from. This object is just a representation.
 */
class root
{
public:
	/**
	 * Constructor.
	 *
	 * @param[in] ptrs an array of @ref object_ptr
	 * @param size the size of the array
	 */
	root(object_ptr* ptrs, std::size_t size) noexcept : _ptrs(ptrs), _size(size)
	{}
	/**
	 * Access the element at the specified index with bounds checking.
	 *
	 * @warning an invalid index results in undefined behavior
	 *
	 * @param index ranges between 0 and the size() inclusive
	 * @returns a reference to the @ref object_ptr at the specified index
	 * @throw exception::bounds_error if the index is out of bounds
	 */
	object_ptr& at(std::size_t index)
	{
		if (index >= _size) {
			BIA_THROW(exception::bounds_error, "out of bounds");
		}

		return _ptrs[index];
	}
	/**
	 * Access the element at the specified index without bounds checking.
	 *
	 * @warning an invalid index results in undefined behavior
	 *
	 * @param index ranges between 0 and the size() inclusive
	 * @returns a reference to the @ref object_ptr at the specified index
	 */
	object_ptr& operator[](std::size_t index) noexcept
	{
		return _ptrs[index];
	}
	bool operator==(const root& other) const noexcept
	{
		return _ptrs == other._ptrs;
	}
	bool operator!=(const root& other) const noexcept
	{
		return _ptrs != other._ptrs;
	}
	/**
	 * The size of the root.
	 *
	 * @returns the size
	 */
	std::size_t size() const noexcept
	{
		return _size;
	}
	/**
	 * Returns the beginning iterator.
	 *
	 * @returns the beginning
	 */
	object_ptr* begin() noexcept
	{
		return _ptrs;
	}
	/**
	 * Returns the end iterator.
	 *
	 * @returns the end
	 */
	object_ptr* end() noexcept
	{
		return _ptrs + _size;
	}

private:
	friend class gc;
	friend class ::std::hash<root>;

	/** the array holding the memory addresses */
	object_ptr* const _ptrs;
	/** the size of the array */
	const std::size_t _size;
};

} // namespace gc
} // namespace bia

namespace std {

template<>
struct hash<bia::gc::root> : private hash<bia::gc::object_ptr*>
{
	typedef bia::gc::root argument_type;
	typedef result_type result_type;

	result_type operator()(const argument_type& s) const noexcept
	{
		return hash<bia::gc::object_ptr*>::operator()(s._ptrs);
	}
};

} // namespace std