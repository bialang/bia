#ifndef BIA_MEMBER_FUNCTION_DYNAMIC_HPP_
#define BIA_MEMBER_FUNCTION_DYNAMIC_HPP_

#include "base.hpp"
#include "context.hpp"

#include <functional>

namespace bia {
namespace member {
namespace function {

typedef std::function<void(Context&)> Dynamic_invokable;

class Dynamic : public Base
{
public:
	Dynamic(Signature signature, Dynamic_invokable invokable) : _signature{ signature }, _invokable{ invokable }
	{}
	void invoke(memory::Frame<true> frame) override
	{
		Context context{ _signature, frame };
		_invokable(context);
		BIA_LOG(INFO, "Dynamic function exit, return set: {}", context.return_is_set());
	}

private:
	Signature _signature;
	Dynamic_invokable _invokable;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
