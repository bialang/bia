#ifndef BIA_CONNECTOR_PARAMETERS_HPP_
#define BIA_CONNECTOR_PARAMETERS_HPP_

#include <algorithm>
#include <bia/gc/stack_view.hpp>
#include <bia/member/member.hpp>
#include <bia/member/native/key_value_pair.hpp>
#include <bia/util/gsl.hpp>
#include <cstdint>
#include <utility>

namespace bia {
namespace connector {

class parameters
{
public:
	parameters(gc::stack_view stack, std::size_t size, std::size_t kwargs) : _stack{ std::move(stack) }
	{
		_size = size;

		if (kwargs) {
			_kwargs.first  = &_stack.arg_at(size - kwargs);
			_kwargs.second = &_stack.arg_at(size - 1) + 1;
		}
	}

	bool empty() const noexcept
	{
		return !_size;
	}
	std::size_t size() const noexcept
	{
		return _size;
	}
	member::member* operator[](util::not_null<util::czstring> name) const
	{
		const auto result = std::lower_bound(
		    _kwargs.first, _kwargs.second, name.get(),
		    [](const gc::stack_view::element_type& left, util::czstring name) {
			    return static_cast<const member::native::key_value_pair*>(left.get())->key()->compare(name) <
			           0;
		    });

		if (result == _kwargs.second ||
		    static_cast<const member::native::key_value_pair*>(result->get())->key()->compare(name.get()) !=
		        0) {
			throw;
		}

		return static_cast<const member::native::key_value_pair*>(result->get())->value();
	}
	member::member* operator[](std::size_t index) const
	{
		return _stack.arg_at(index).get();
	}

private:
	gc::stack_view _stack;
	std::size_t _size;
	std::pair<gc::stack_view::element_type*, gc::stack_view::element_type*> _kwargs;
};

} // namespace connector
} // namespace bia

#endif
