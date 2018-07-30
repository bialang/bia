#include "allocator.hpp"
#include "max_member_size.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

size_t allocator::block_size() noexcept
{
	return framework::max_member_size;
}

}
}
}