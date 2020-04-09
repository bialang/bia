#ifndef BIA_GC_STACK_HPP_
#define BIA_GC_STACK_HPP_

#include "object/pointer.hpp"
#include "object/base.hpp"

#include <exception/bounds_error.hpp>
#include <functional>
#include <memory>

namespace bia {
namespace gc {

class stack
{
public:
	typedef object::pointer<object::base> element_type;

	stack(element_type* data, std::size_t size) noexcept
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
	element_type& push()
	{
		if (_cursor >= _max_size) {
			BIA_THROW(exception::bounds_error, "stack overflow");
		}

		return _data[_cursor++];
	}
	element_type& at(std::size_t index)
	{
		if (index >= _cursor) {
			BIA_THROW(exception::bounds_error, "out of bounds");
		}

		return _data[index];
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
	bool operator==(const stack& other) const noexcept
	{
		return _data == other._data;
	}

private:
	friend class token;

	element_type* _data   = nullptr;
	std::size_t _cursor   = 0;
	std::size_t _max_size = 0;
};

} // namespace gc
} // namespace bia

template<>
struct std::hash<bia::gc::stack> : private hash<bia::gc::stack::element_type*>
{
	typedef bia::gc::stack argument_type;
	typedef result_type result_type;

	result_type operator()(const argument_type& s) const noexcept
	{
		return hash<bia::gc::stack::element_type*>::operator()(s.data());
	}
};

#endif