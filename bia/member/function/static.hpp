#ifndef BIA_MEMBER_FUNCTION_STATIC_HPP_
#define BIA_MEMBER_FUNCTION_STATIC_HPP_

#include "base.hpp"

namespace bia {
namespace member {
namespace function {

template<typename Return, typename... Arguments>
class Static : public Base
{
public:
	typedef Return (*Function)(Arguments...);

	Static(Function pointer) noexcept : _pointer{ pointer }
	{}
	void invoke() override
	{
		_pointer();
	}

private:
	Function _pointer;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
