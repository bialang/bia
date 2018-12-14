#pragma once

#include "config.hpp"
#include "allocator.hpp"
#include "member_allocator.hpp"
#include "big_int_allocator.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

/**
 * @brief A simple implementation of @ref allocator, @ref member_allocator and @red big_int_allocator.
 *
 * A simple allocator which allocates memory for the machine context. All memory will be allocated using standard function without caching.
*/
class simple_allocator : public allocator, public member_allocator, public big_int_allocator
{
public:
	BIA_EXPORT virtual void deallocate(universal_allocation _allocation) override;
	BIA_EXPORT virtual void deallocate_member(allocation<framework::member> _allocation) override;
	BIA_EXPORT virtual void deallocate_big_int(big_int_allocation _allocation) override;
	BIA_EXPORT virtual universal_allocation reallocate(universal_allocation _allocation, size_type _size) override;
	BIA_EXPORT virtual universal_allocation commit(universal_allocation _allocation, size_type _size) override;
	BIA_EXPORT virtual universal_allocation allocate(size_type _size) override;
	BIA_EXPORT virtual allocation<framework::member> allocate_member() override;
	BIA_EXPORT virtual big_int_allocation allocate_big_int() override;
	BIA_EXPORT virtual universal_allocation prepare(size_type _size) override;
};

}
}
}