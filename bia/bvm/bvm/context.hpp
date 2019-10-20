#pragma once

#include <gc/gc.hpp>
#include <stack/stack.hpp>

namespace bia {
namespace bvm {

class context
{
public:
	context(stack::stack& s, gc::gc& g) : s(s), g(g)
	{}

	stack::stack& stack() noexcept
	{
		return s;
	}
	gc::gc& gc() noexcept
	{
		return g;
	}

private:
	stack::stack& s;
	gc::gc& g;
};

} // namespace bvm
} // namespace bia