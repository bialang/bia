#pragma once

#include <type_traits>

#include "allocator.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

template<size_type... Block_sizes>
class block_allocator : public allocator
{
public:
	/** The count of available block sizes. */
	constexpr static size_t block_count = sizeof...(Block_sizes);

	template<size_type Block_size>
	void deallocate_block(universal_allocation _block)
	{
		deallocate_block(universal_allocation _block, Block_size, block_size_id<Block_size, Block_sizes...>());
	}
	template<size_type Block_size>
	universal_allocation allocate_block()
	{
		return allocate_block(Block_size, block_size_id<Block_size, Block_sizes...>());
	}
protected:
	virtual void deallocate_block(universal_allocation _block, size_type _block_size, size_t _block_id) = 0;
	virtual universal_allocation allocate_block(size_type _block_size, size_t _block_id) = 0;
	template<size_type Size, size_type Block_size, size_type... Remaining_block_sizes>
	constexpr static typename std::enable_if<Size == Block_size, size_t>::type block_size_id() noexcept
	{
		return 0;
	}
	template<size_type Size, size_type Block_size, size_type... Remaining_block_sizes>
	constexpr static typename std::enable_if<(Size != Block_size && sizeof...(Remaining_block_sizes) > 0), size_t>::type block_size_id() noexcept
	{
		return block_size_id<Size, Remaining_block_sizes...>() + 1;
	}
private:
};

}
}
}