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
	template<typename Type>
	void destroy_block0(allocation<Type> _allocation)
	{
		// Destroy
		reinterpret_cast<Type*>(_allocation.first)->~Type();

		deallocate_block0(cast_allocation<void>(_allocation));
	}
	virtual universal_allocation allocate_block0() = 0;
	template<typename Base, typename Deriviate = Base, typename... Arguments>
	allocation<Base> construct_block0(Arguments &&... _arguments)
	{
		static_assert(sizeof(Deriviate) <= block_size0, "Block size exceeded.");

		auto _allocation = allocate_block0();

		// Construct
		new(_allocation.first) Deriviate(std::forward<Arguments>(_arguments)...);

		return cast_allocation<Base>(_allocation);
	}
};

template<size_type Block_size0, size_type Block_size1>
class block_allocator1 : public block_allocator0<Block_size0>
{
public:
	constexpr static auto block_size1 = Block_size1;

	virtual void deallocate_block1(universal_allocation _block) = 0;
	virtual universal_allocation allocate_block1() = 0;
};

}
}
}