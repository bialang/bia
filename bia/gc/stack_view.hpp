#ifndef BIA_GC_STACK_VIEW_HPP_
#define BIA_GC_STACK_VIEW_HPP_

#include "object/base.hpp"
#include "object/pointer.hpp"

#include <bia/exception/bounds_error.hpp>

namespace bia {
namespace member {

class member;

} // namespace member
namespace gc {

class stack_view
{
public:
	typedef object::pointer<member::member> element_type;

	stack_view(element_type* base, std::size_t size) noexcept : _base{ base }, _max_size{ size }
	{}
	void drop(std::size_t count)
	{
		if (count > _cursor) {
			BIA_THROW(exception::bounds_error, "stack underflow");
		}

		_cursor -= count;
	}
	std::size_t cursor() const noexcept
	{
		return _cursor;
	}
	std::size_t arg_count() const noexcept
	{
		return _args;
	}
	element_type& local_at(std::size_t index)
	{
		if (index >= _max_size) {
			BIA_THROW(exception::bounds_error, "out of bounds");
		} else if (index > _cursor) {
			_cursor = index;
		}

		return _base[index];
	}
	element_type& arg_at(std::size_t index)
	{
		if (index >= _max_size) {
			BIA_THROW(exception::bounds_error, "out of bounds");
		} else if (index > _args) {
			_args = index;
		}

		return _base[_max_size - index];
	}
	stack_view sub_view(std::size_t count) const
	{
		if (count > _args) {
			BIA_THROW(exception::bounds_error, "out of arg bound");
		}

		stack_view s{ _base + _cursor + 1, _max_size - (_cursor + 1) - (_args - count) };

		s._args = count;

		return s;
	}

private:
	friend class token;

	element_type* const _base;
	const std::size_t _max_size;
	std::size_t _cursor = 0;
	std::size_t _args   = 0;
};

} // namespace gc
} // namespace bia

#endif
