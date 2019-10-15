#pragma once

#include <gc/gc.hpp>
#include <stack/stack.hpp>

namespace bia {
namespace bvm {

class context
{
public:
	context(gc::gc& g)
	{
		this->g = &g;
	}

	stack::stack& stack() noexcept
	{}
	gc::gc& gc() noexcept
	{
		return g;
	}

private:
	gc::gc* g;
};

} // namespace bvm
} // namespace bia