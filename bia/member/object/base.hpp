#ifndef BIA_MEMBER_OBJECT_BASE_HPP_
#define BIA_MEMBER_OBJECT_BASE_HPP_

#include <bia/memory/frame.hpp>
#include <bia/memory/gc/types.hpp>
#include <cstdint>

namespace bia {
namespace member {
namespace object {

class Base : public memory::gc::Base
{
public:
	virtual void store_to(std::size_t offset, memory::Frame<true> frame) = 0;
};

} // namespace object
} // namespace member
} // namespace bia

#endif
