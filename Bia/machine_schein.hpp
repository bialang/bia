#pragma once

#include <vector>

#include "allocator.hpp"


namespace bia
{
namespace machine
{

class machine_schein
{
public:
	/**
	 * Constructor.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @param	[in]	_allocator	Defines the memory allocator.
	*/
	machine_schein(allocator * _allocator) noexcept;
	machine_schein(const machine_schein & _copy) = delete;
	machine_schein(machine_schein && _rvalue) = default;
	~machine_schein();
	/**
	 * Registers an allocation. Must be of allocator::MEMORY_TYPE::NORMAL.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @param	_allocation	Defines the allocation.
	*/
	void register_allocation(allocator::universal_allocation _allocation) noexcept;
	/**
	 * Deletes all registered allocations.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @throws	See allocator::deallocate().
	*/
	void delete_all_allocations();
	/**
	 * Returns the memory allocator.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @return	A pointer to the allocator.
	*/
	allocator * get_allocator() noexcept;
	/**
	 * Move operator.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @param	[in,out]	_rvalue	Defines the value that should be moved.
	 *
	 * @throws	See machine_schein::delete_all_allocations().
	 *
	 * @return	This.
	*/
	machine_schein & operator=(machine_schein && _rvalue);

private:
	/**	Defines the memory allocator.	*/
	allocator * _allocator;
	/**	Stores all the registered allocations.	*/
	std::vector<allocator::universal_allocation> _allocated;
};

}
}