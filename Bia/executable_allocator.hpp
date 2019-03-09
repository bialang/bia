#pragma once

#include "allocator.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

/**
 * @brief An allocator for executable memory.
 *
 * @see @ref simple_executable_allocator
*/
class executable_allocator
{
public:
	enum PROTECTION_FLAGS
	{
		/** Specifies normal read and write access. */
		PF_READ_WRITE = 0x1,
		/** Specifies executable memory. */
		PF_EXECUTE = 0x4
	};

	/**
	 * Deallocates executable memory.
	 *
	 * @since 3.71.149.809
	 * @date 27-Dec-18
	 *
	 * @param _allocation The allocation created by allocate_executable().
	 *
	 * @throws exception::memory_error If the specified allocation is invalid.
	*/
	virtual void deallocate_executable(universal_allocation _allocation) = 0;
	/**
	 * Changes the protection of an allocation from this object.
	 *
	 * @remarks The @a _allocation should be created by allocate_executable().
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _allocation The allocation created by allocate_executable().
	 * @param _protection The protection flags. See @ref PROTECTION_FLAGS.
	 *
	 * @throws exception::memory_error If the protection cannot be changed or if the parameters are invalid.
	*/
	virtual void protect_executable(universal_allocation _allocation, int _protection) = 0;
	/**
	 * Allocates executable memory.
	 *
	 * @since 3.71.149.809
	 * @date 27-Dec-18
	 *
	 * @param _size The size of the allocation in bytes.
	 *
	 * @throws exception::memory_error If the specified allocation is invalid.
	 *
	 * @return The executable memory.
	*/
	virtual universal_allocation allocate_executable(size_type _size) = 0;
};

}
}
}