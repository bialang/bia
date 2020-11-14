#include "function.hpp"

#include "../invoke_context.hpp"

#include <bia/assembler/disassembler.hpp>
#include <bia/bvm/bvm.hpp>
#include <bia/config.hpp>
#include <iostream>

using namespace bia::member::function;

bia::gc::gcable<bia::member::member> function::invoke(parameters_type params, invoke_context& context)
{
	// apply bindings
	for (const auto& i : _bindings) {
		context.token.set(params.stack().local_at(i.first), i.second);
	}

#if BIA_DEVELOPER_DISASSEMBLY
	assembler::disassemble({ _code.get(), _size }, context.resources, std::cout);
#endif

	return bvm::bvm::execute(context.context, { _code.get(), _size }, context.resources, params.stack(),
	                         context.token);
}
