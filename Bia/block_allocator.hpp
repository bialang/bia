#pragma once

#include <utility>

#include "allocator.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

template<size_type Block_size>
class block_allocator : public virtual allocator
{
public:
	constexpr static auto block_size = Block_size;

	virtual void deallocate_block(universal_allocation _block) = 0;
	template<typename Type>
	void destroy_block(allocation<Type> _allocation)
	{
		// Destroy
		reinterpret_cast<Type*>(_allocation.first)->~Type();

		deallocate_block(cast_allocation<void>(_allocation));
	}
	virtual universal_allocation allocate_block() = 0;
	template<typename Base, typename Deriviate = Base, typename... Arguments>
	allocation<Base> construct_block(Arguments &&... _arguments)
	{
		static_assert(sizeof(Deriviate) <= block_size, "Block size exceeded.");

		auto _allocation = allocate_block();

		// Construct
		new(_allocation.first) Deriviate(std::forward<Arguments>(_arguments)...);

		return cast_allocation<Base>(_allocation);
	}
};

}
}
}