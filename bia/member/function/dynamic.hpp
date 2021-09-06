#ifndef BIA_MEMBER_FUNCTION_DYNAMIC_HPP_
#define BIA_MEMBER_FUNCTION_DYNAMIC_HPP_

#include "base.hpp"
#include "context.hpp"

#include <functional>

namespace bia {
namespace member {
namespace function {

typedef std::function<void(Context&)> Dynamic_callback;

class Dynamic : public Base
{
public:
	Dynamic(Signature signature, Dynamic_callback function) : _signature{ signature }, _function{ function }
	{}
	void invoke(memory::Frame<true> frame) override
	{
		// create parameters with signature
		Context context{ _signature, frame };

		// call the function
		_function(context);
	}

private:
	Signature _signature;
	Dynamic_callback _function;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
