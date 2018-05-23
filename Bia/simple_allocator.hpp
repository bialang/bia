#pragma once

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
	virtual void deallocate(universal_allocation _allocation) override;
	virtual void deallocate_blocks(universal_allocation _blocks) override;
	virtual universal_allocation commit(universal_allocation _allocation, size_t _size) override;
	virtual universal_allocation allocate(size_t _size) override;
	virtual universal_allocation allocate_blocks(size_t _count) override;
	virtual universal_allocation prepare(size_t _size) override;
};

}
}
}