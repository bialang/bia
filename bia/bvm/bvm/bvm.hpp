#pragma once

#include "context.hpp"

#include <compiler/code.hpp>
#include <connector/connector_impl.hpp>

namespace bia {
namespace bvm {

class bvm
{
public:
	/*
	 Executes the given code object.

	 @param[in,out] context is the engine context
	 @param code is the executable bia code
	*/
	void execute(context& context, const compiler::code& code);
};

} // namespace bvm
} // namespace bia