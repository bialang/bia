#pragma once

#include "config.hpp"
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
	BIA_EXPORT virtual void deallocate(universal_allocation _allocation) override;
	BIA_EXPORT virtual void protect(universal_allocation _allocation, int _protection) override;
	BIA_EXPORT virtual universal_allocation reallocate(universal_allocation _allocation, size_type _size) override;
	BIA_EXPORT virtual universal_allocation commit(universal_allocation _allocation, size_type _size) override;
	BIA_EXPORT virtual universal_allocation allocate(size_type _size) override;
	BIA_EXPORT virtual universal_allocation prepare(size_type _size) override;
};

}
}
}