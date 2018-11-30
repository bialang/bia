#pragma once

#include <type_traits>

#include "allocator.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

template<size_type Block_size0>
class block_allocator0 : public allocator
{
public:
	constexpr static auto block_size0 = Block_size0;

	virtual void deallocate_block0(universal_allocation _block) = 0;
	virtual universal_allocation allocate_block0() = 0;
};

template<size_type Block_size0, size_type Block_size1>
class block_allocator1 : public block_allocator0<block_allocator0>
{
public:
	constexpr static auto block_size1 = Block_size1;

	virtual void deallocate_block1(universal_allocation _block) = 0;
	virtual universal_allocation allocate_block1() = 0;
};

}
}
}