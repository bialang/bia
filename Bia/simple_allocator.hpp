#pragma once

#include "config.hpp"
#include "allocator.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

/**
 * @brief A simple implementation of @ref allocator.
 *
 * A simple allocator which allocates 'normal' memory without no checking. All memory will be allocated using standard function without caching.
*/
class simple_allocator : public allocator
{
public:
	BIA_EXPORT virtual void deallocate(universal_allocation _allocation) override;
	BIA_EXPORT virtual void deallocate_blocks(universal_allocation _blocks) override;
	BIA_EXPORT virtual universal_allocation reallocate(universal_allocation _allocation, size_type _size) override;
	BIA_EXPORT virtual universal_allocation commit(universal_allocation _allocation, size_type _size) override;
	BIA_EXPORT virtual universal_allocation allocate(size_type _size) override;
	BIA_EXPORT virtual universal_allocation allocate_blocks(size_type _count) override;
	BIA_EXPORT virtual universal_allocation prepare(size_type _size) override;
};

}
}
}