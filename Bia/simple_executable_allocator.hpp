#pragma once

#include "executable_allocator.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

/**
 * @brief A simple implementation of @ref executable_allocator.
 *
 * A simple allocator which can allocate executable memory without no checking. All memory will be allocated using standard function without caching.
*/
class simple_executable_allocator : public executable_allocator
{
public:
	virtual void deallocate(universal_allocation _allocation) override;
	virtual void deallocate_blocks(universal_allocation _blocks) override;
	virtual void protect(universal_allocation _allocation, int _protection) override;
	virtual universal_allocation reallocate(universal_allocation _allocation, size_type _size) override;
	virtual universal_allocation commit(universal_allocation _allocation, size_type _size) override;
	virtual universal_allocation allocate(size_type _size) override;
	virtual universal_allocation allocate_blocks(size_type _count) override;
	virtual universal_allocation prepare(size_type _size) override;
};

}
}
}