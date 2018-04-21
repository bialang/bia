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
 * A simple allocator which does no checking. All memory will be allocated using standard function without caching.
*/
class simple_allocator : public allocator
{
public:
	virtual void commit_allocation(universal_allocation _allocation, size_t _size) override;
	virtual void deallocate(universal_allocation _allocation, MEMORY_TYPE _type) override;
	virtual void deallocate_blocks(universal_allocation _allocation, MEMORY_TYPE _type) override;
	virtual void change_protection(universal_allocation _allocation, int _protection) override;
	virtual universal_allocation allocate(size_t _size, MEMORY_TYPE _type) override;
	virtual universal_allocation allocate_blocks(size_t _count, MEMORY_TYPE _type) override;
	virtual universal_allocation reserve_allocation(size_t _max_size, MEMORY_TYPE _type) override;
};

}
}
}