#pragma once

#include "object_ptr.hpp"

#include <cstddef>
#include <functional>

namespace bia {
namespace gc {

/*
 The root array created by the gc where all gc monitored memory originates from.
*/
class root
{
public:
	root(object_ptr* ptrs, std::size_t size) noexcept : ptrs(ptrs), s(size)
	{}
	/*
	 Access the element at the specified index.

	 @param index ranges between 0 and the size() inclusive; if the index is invalid, the behavior is undefined
	*/
	object_ptr& operator[](std::size_t index) noexcept
	{
		return ptrs[index];
	}
	const object_ptr& operator[](std::size_t index) const noexcept
	{
		return ptrs[index];
	}
	bool operator==(const root& other) const noexcept
	{
		return ptrs == other.ptrs;
	}
	bool operator!=(const root& other) const noexcept
	{
		return ptrs != other.ptrs;
	}
	bool operator<(const root& other) const noexcept
	{
		return ptrs < other.ptrs;
	}
	bool operator<=(const root& other) const noexcept
	{
		return ptrs <= other.ptrs;
	}
	bool operator>(const root& other) const noexcept
	{
		return ptrs > other.ptrs;
	}
	bool operator>=(const root& other) const noexcept
	{
		return ptrs >= other.ptrs;
	}
	std::size_t size() const noexcept
	{
		return s;
	}

private:
	friend class gc;
	friend class ::std::hash<root>;

	/* the array holding the memory addresses */
	object_ptr* const ptrs;
	/* the size of the array */
	std::size_t const s;
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
		return hash<bia::gc::object_ptr*>::operator()(s.ptrs);
	}
};

} // namespace std