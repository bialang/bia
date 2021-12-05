#ifndef BIA_MEMBER_OBJECT_BASE_HPP_
#define BIA_MEMBER_OBJECT_BASE_HPP_

#include <bia/memory/frame.hpp>

namespace bia {
namespace member {
namespace object {

class Base : public memory::gc::Base
{
public:
	virtual memory::Frame<true> frame() noexcept = 0;
};

} // namespace object
} // namespace member
} // namespace bia

#endif
