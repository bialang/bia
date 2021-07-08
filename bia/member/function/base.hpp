#ifndef BIA_MEMBER_FUNCTION_BASE_HPP_
#define BIA_MEMBER_FUNCTION_BASE_HPP_

#include <bia/memory/frame.hpp>
#include <bia/memory/gc/types.hpp>

namespace bia {
namespace member {
namespace function {

class Base : public memory::gc::Base
{
public:
	virtual void invoke(memory::Frame<true> frame) = 0;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
