#include "allocator.hpp"
#include "max_member_size.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

size_t allocator::get_block_size() const noexcept
{
	return framework::max_member_size;
}

}
}
}