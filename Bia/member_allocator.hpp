#pragma once

#include <utility>
#include <type_traits>

#include "allocator.hpp"
#include "max_member_size.hpp"
#include "member.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

/**
 * @brief Allocates enough space for all members.
 *
 * A memory allocator which allocates memory for all members in the framework.
 *
 * @see @ref framework::member
*/
class member_allocator
{
public:
	/** The size of one member allocation in bytes. */
	constexpr static auto member_allocation_size = framework::max_member_size;

	/**
	 * Destructor.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	*/
	virtual ~member_allocator() = default;
	/**
	 * Deallocates the member allocation.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @param _allocation The member allocation.
	 *
	 * @throws exception::memory_error If the specified allocation wasn't allocated by allocate_member().
	*/
	virtual void deallocate_member(allocation<framework::member> _allocation) = 0;
	/**
	 * Destroys and deallocates the given member.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @param _member The member.
	 *
	 * @throws See deallocate_member().
	 * @throws See the destructor of the member.
	*/
	void destroy_member(allocation<framework::member> _member)
	{
		// Destroy
		reinterpret_cast<framework::member*>(_member.first)->~member();

		deallocate_member(_member);
	}
	/**
	 * Allocates memory for one member.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @throws exception::memory_error If no memory could be allocated.
	 *
	 * @return The allocated, but uninitialized member.
	*/
	virtual allocation<framework::member> allocate_member() = 0;
	/**
	 * Allocates and constructs a member of the specified type @a Type.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @tparam Type A deriviate of @ref framework::member which size must be less or equal to @ref member_allocation_size.
	 * @tparam Arguments The type of the arguments.
	 *
	 * @param _arguments The arguments passed to the constructor of @a Type.
	 *
	 * @throws See allocate_member().
	 * @throws See the constructor of @a Type.
	 *
	 * @return The constructed member.
	*/
	template<typename Type, typename... Arguments>
	allocation<framework::member> construct_member(Arguments &&... _arguments)
	{
		static_assert(sizeof(Type) <= member_allocation_size, "Member size exceeded.");
		static_assert(std::is_base_of<framework::member, Type>::value, "Type must be a deriviate of framework::member.");

		auto _allocation = allocate_member();

		// Construct
		new(_allocation.first) Type(std::forward<Arguments>(_arguments)...);

		return _allocation;
	}
};

}
}
}