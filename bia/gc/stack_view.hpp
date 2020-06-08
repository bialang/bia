#ifndef BIA_GC_STACK_VIEW_HPP_
#define BIA_GC_STACK_VIEW_HPP_

#include "object/base.hpp"
#include "object/pointer.hpp"

#include <bia/exception/bounds_error.hpp>
#include <functional>
#include <memory>

namespace bia {
namespace member {

class member;

} // namespace member
namespace gc {

class stack_view
{
public:
	typedef object::pointer<member::member> element_type;

	stack_view(element_type* data, std::size_t size) noexcept
	{
		_data     = data;
		_max_size = size;
	}
	std::size_t size() const noexcept
	{
		return _cursor;
	}
	std::size_t max_size() const noexcept
	{
		return _max_size;
	}
	void drop(std::size_t count)
	{
		if (count > _cursor) {
			BIA_THROW(exception::bounds_error, "stack underflow");
		}

		_cursor -= count;
	}
	element_type& pop()
	{
		if (!_cursor) {
			BIA_THROW(exception::bounds_error, "stack underflow");
		}

		return _data[--_cursor];
	}
	element_type& tos() const
	{
		if (!_cursor) {
			BIA_THROW(exception::bounds_error, "empty stack");
		}

		return _data[_cursor - 1];
	}
	element_type& push()
	{
		if (_cursor >= _max_size) {
			BIA_THROW(exception::bounds_error, "stack overflow");
		}

		return _data[_cursor++];
	}
	element_type& local_at(std::size_t index) const
	{
		if (index >= _cursor) {
			BIA_THROW(exception::bounds_error, "out of bounds");
		}

		return _data[index];
	}
	element_type& arg_at(std::size_t index) const
	{
		if (index >= _args) {
			BIA_THROW(exception::bounds_error, "out of bounds");
		}

		return *(_data - _args + index);
	}
	element_type* data() const noexcept
	{
		return _data;
	}
	element_type* begin() const noexcept
	{
		return _data;
	}
	element_type* end() const noexcept
	{
		return _data + _max_size;
	}
	stack_view frame(std::size_t arg_count) const
	{
		BIA_EXPECTS(arg_count <= _cursor);

		stack_view s{ _data + _cursor, _max_size - _cursor };

		s._args = arg_count;

		return s;
	}
	bool operator==(const stack_view& other) const noexcept
	{
		return _data == other._data;
	}

private:
	friend class token;

	element_type* _data   = nullptr;
	std::size_t _cursor   = 0;
	std::size_t _max_size = 0;
	std::size_t _args     = 0;
};

} // namespace gc
} // namespace bia

template<>
struct std::hash<bia::gc::stack_view> : private hash<bia::gc::stack_view::element_type*>
{
	typedef bia::gc::stack_view argument_type;
	typedef result_type result_type;

	result_type operator()(const argument_type& s) const noexcept
	{
		return hash<bia::gc::stack_view::element_type*>::operator()(s.data());
	}
};

#endif
