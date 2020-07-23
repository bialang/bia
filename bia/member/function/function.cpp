#include "function.hpp"

#include "../invoke_context.hpp"

#include <bia/bvm/bvm.hpp>

using namespace bia::member::function;

bia::gc::gcable<bia::member::member> function::invoke(parameters_type params, invoke_context& context)
{
	return bvm::bvm::execute(context.context, { _code.get(), _size }, context.resources, context.parent_stack,
	                         context.token);
}
