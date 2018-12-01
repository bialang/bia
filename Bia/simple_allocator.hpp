#pragma once

#include "config.hpp"
#include "block_allocator.hpp"
#include "max_member_size.hpp"
#include "big_int.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

/**
 * @brief A simple implementation of @ref allocator.
 *
 * A simple allocator which allocates 'normal' memory without checking. All memory will be allocated using standard function without caching.
*/
class simple_allocator : public block_allocator<framework::max_member_size>, public block_allocator<sizeof(dependency::big_int)>
{
public:
	BIA_EXPORT virtual void deallocate(universal_allocation _allocation) override;
	BIA_EXPORT virtual void block_allocator<framework::max_member_size>::deallocate_block(universal_allocation _block) override;
	BIA_EXPORT virtual void block_allocator<sizeof(dependency::big_int)>::deallocate_block(universal_allocation _block) override;
	BIA_EXPORT virtual universal_allocation reallocate(universal_allocation _allocation, size_type _size) override;
	BIA_EXPORT virtual universal_allocation commit(universal_allocation _allocation, size_type _size) override;
	BIA_EXPORT virtual universal_allocation allocate(size_type _size) override;
	BIA_EXPORT virtual universal_allocation block_allocator<framework::max_member_size>::allocate_block() override;
	BIA_EXPORT virtual universal_allocation block_allocator<sizeof(dependency::big_int)>::allocate_block() override;
	BIA_EXPORT virtual universal_allocation prepare(size_type _size) override;
};

}
}
}