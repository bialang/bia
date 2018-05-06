#pragma once

#include <vector>

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
	machine_schein(memory::allocator * _allocator, memory::executable_allocator * _executable_allocator) noexcept;
	machine_schein(const machine_schein & _copy) = delete;
	machine_schein(machine_schein && _rvalue) = default;
	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @throws See delete_all_allocations().
	*/
	~machine_schein();
	/**
	 * Registers an allocation. Must be created by get_allocator().
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _allocation Defines the allocation.
	*/
	void register_allocation(memory::executable_allocator::universal_allocation _allocation) noexcept;
	/**
	 * Deletes all registered allocations.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @throws See memory::allocator::deallocate().
	*/
	void delete_all_allocations();
	/**
	 * Returns the normal memory allocator.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @return The pointer to the allocator.
	*/
	memory::allocator * get_allocator() noexcept;
	/**
	 * Returns the executable memory allocator.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @return The pointer to the allocator.
	*/
	memory::executable_allocator * get_executable_allocator() noexcept;
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
	machine_schein & operator=(machine_schein && _rvalue);

private:
	/** The memory allocator for normal memory. */
	memory::allocator * _allocator;
	/** The memory allocator for executable memory. */
	memory::executable_allocator * _executable_allocator;
	/** Stores all the registered allocations. */
	std::vector<memory::allocator::universal_allocation> _allocated;
};

}
}