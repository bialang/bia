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

private:
	friend class framework::member;

	/* the in the current thread active gc */
	static thread_local gc::gc* active_gc;
};

} // namespace bvm
} // namespace bia