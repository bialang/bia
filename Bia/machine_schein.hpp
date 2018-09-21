#pragma once

#include <vector>

#include "config.hpp"
#include "executable_allocator.hpp"


namespace bia
{
namespace machine
{

/**
 * @brief Contains information about machine code.
 *
 * Keeps track of all allocations of one machine code instance.
 *
 * @see @ref machine_code
*/
class machine_schein
{
public:
	/**
	 * Constructor.
	 *
	 * @remarks During the lifetime of this object the allocators have to stay vaild. They will not be released at any time.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param [in] _allocator The allocator for normal memory.
	 * @param [in] _executable_allocator The allocator for executable memory.
	*/
	BIA_EXPORT machine_schein(memory::allocator * _allocator, memory::executable_allocator * _executable_allocator) noexcept;
	machine_schein(const machine_schein & _copy) = delete;
	machine_schein(machine_schein && _rvalue) noexcept = default;
	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @throws See delete_all_allocations().
	*/
	BIA_EXPORT ~machine_schein();
	/**
	 * Registers an allocation. Must be created by get_allocator().
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _allocation Defines the allocation.
	 *
	 * @throws See std::vector::push_back().
	*/
	BIA_EXPORT void register_allocation(memory::universal_allocation _allocation);
	/**
	 * Deletes all registered allocations.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @throws See memory::allocator::deallocate().
	*/
	BIA_EXPORT void delete_all_allocations();
	/**
	 * Returns the normal memory allocator.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @return The pointer to the allocator.
	*/
	BIA_EXPORT memory::allocator * allocator() noexcept;
	/**
	 * Returns the executable memory allocator.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @return The pointer to the allocator.
	*/
	BIA_EXPORT memory::executable_allocator * executable_allocator() noexcept;
	/**
	 * Move operator.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param [in,out] _rvalue Defines the value that should be moved.
	 *
	 * @throws See delete_all_allocations().
	 *
	 * @return This.
	*/
	BIA_EXPORT machine_schein & operator=(machine_schein && _rvalue);

private:
	/** The memory allocator for normal memory. */
	memory::allocator * _allocator;
	/** The memory allocator for executable memory. */
	memory::executable_allocator * _executable_allocator;
	/** Stores all the registered allocations. */
	std::vector<memory::universal_allocation> _allocated;
};

}
}