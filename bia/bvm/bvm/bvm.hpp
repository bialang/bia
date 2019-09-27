#pragma once

#include "code.hpp"
#include "context.hpp"

namespace bia {
namespace bvm {

class bvm
{
public:
	enum class OPTIMIZATION
	{
		NONE,
		FULL
	};

	/*
	 Executes the given code object.

	 @param[in,out] context is the engine context
	 @param code is the executable bia code
	*/
	void execute(context& context, const code& code);
};

} // namespace bvm
} // namespace bia