#ifndef BIA_GC_STACK_HPP_
#define BIA_GC_STACK_HPP_

#include "object/pointer.hpp"

#include <exception/bounds_error.hpp>
#include <memory>

namespace bia {
namespace member {

class member;

} // namespace member

namespace gc {

class stack
{
public:
	typedef object::pointer<member::member> element_type;

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

private:
	friend class token;

	element_type* _data   = nullptr;
	std::size_t _cursor   = 0;
	std::size_t _max_size = 0;
};

} // namespace gc
} // namespace bia

#endif