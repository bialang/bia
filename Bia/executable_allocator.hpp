#pragma once

#include "allocator.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

/**
 * @brief An extension to @ref allocator.
 *
 * An allocation which can change the protection of memory.
 *
 * @see @ref simple_executable_allocator
*/
class executable_allocator : public allocator
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
	 * Changes the protection of an allocation from this object.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _allocation The allocation.
	 * @param _protection The protection flags. See @ref PROTECTION_FLAGS.
	 *
	 * @throws exception::memory_error If the protection cannot be changed or if the specified flags are invalid.
	*/
	virtual void protect(universal_allocation _allocation, int _protection) = 0;
};

}
}
}