#ifndef BIA_CONNECTOR_PARAMETERS_HPP_
#define BIA_CONNECTOR_PARAMETERS_HPP_

#include <bia/gc/stack_view.hpp>
#include <bia/member/member.hpp>
#include <cstdint>

namespace bia {
namespace connector {

class parameters
{
public:
	parameters(gc::stack_view& stack, std::size_t size) : _stack{ stack }
	{
		_size = size;
	}

	bool empty() const noexcept
	{
		return !_size;
	}
	std::size_t size() const noexcept
	{
		return _size;
	}
	member::member* operator[](std::size_t index) const
	{
		return _stack.arg_at(index).get();
	}

private:
	gc::stack_view& _stack;
	std::size_t _size;
};

} // namespace connector
} // namespace bia

#endif
