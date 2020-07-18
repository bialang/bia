#ifndef BIA_CONNECTOR_PARAMETERS_HPP_
#define BIA_CONNECTOR_PARAMETERS_HPP_

#include "stack_iterator.hpp"

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
	parameters(gc::stack_view::call_frame call_frame) : _stack{ std::move(call_frame.stack) }
	{
		_size = call_frame.arg_count + call_frame.kwarg_count;

		if (call_frame.kwarg_count) {
			_kwargs = { { &_stack.arg_at(call_frame.arg_count) }, call_frame.kwarg_count };
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
	stack_iterator<member::member, true> begin() noexcept
	{
		return _size ? &_stack.arg_at(0) : nullptr;
	}
	stack_iterator<member::member, true> end() noexcept
	{
		return _size ? &_stack.arg_at(_size - 1) + 1 : nullptr;
	}
	util::span<stack_iterator<member::member, true>> positionals() noexcept
	{
		const auto end = _size - _kwargs.size();

		// empty
		if (!end) {
			return { {}, 0 };
		}

		return { { &_stack.arg_at(0) }, end };
	}
	util::span<stack_iterator<member::native::key_value_pair, true>> kwargs() const noexcept
	{
		return _kwargs;
	}
	std::pair<member::member*, bool> operator[](util::not_null<util::czstring> name) const noexcept
	{
		const auto result =
		    std::lower_bound(_kwargs.begin(), _kwargs.end(), name.get(),
		                     [](const member::native::key_value_pair* left, util::czstring name) {
			                     return left->key()->compare(name) < 0;
		                     });

		if (result == _kwargs.end() || result->key()->compare(name.get()) != 0) {
			return { nullptr, false };
		}

		return { result->value(), true };
	}
	member::member* operator[](std::size_t index)
	{
		return _stack.arg_at(index).get();
	}

private:
	gc::stack_view _stack;
	std::size_t _size;
	util::span<stack_iterator<member::native::key_value_pair, true>> _kwargs;
};

} // namespace connector
} // namespace bia

#endif
