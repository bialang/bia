#pragma once

#include <cstdint>

#include "config.hpp"
#include "allocator.hpp"
#include "member.hpp"


namespace bia
{
namespace machine
{

/**
 * @brief A simple stack.
 *
 * A simple stack used by the machine context.
 *
 * @see @ref machine_context
*/
class machine_stack
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.65.132.734
	 * @date 30-Jun-18
	 *
	 * @param [in] _allocator The memory allocator.
	 * @param _size The stack size in bytes.
	 *
	 * @throws See memory::allocator::allocate().
	*/
	BIA_EXPORT machine_stack(memory::allocator * _allocator, size_t _size);
	machine_stack(const machine_stack & _copy) = delete;
	/**
	 * Move-Constructor.
	 *
	 * @since 3.68.140.788
	 * @date 16-Sep-18
	 *
	 * @param [in,out] _move The instance that should be moved.
	*/
	BIA_EXPORT machine_stack(machine_stack && _move) noexcept;
	/**
	 * Destructor.
	 *
	 * @since 3.65.132.734
	 * @date 30-Jun-18
	 *
	 * @throws See memory::allocator::deallocate().
	*/
	BIA_EXPORT ~machine_stack();
	/**
	 * Pops the variables from the stack.
	 *
	 * @since 3.65.132.734
	 * @date 30-Jun-18
	 *
	 * @param _member_count The amount of member variables.
	 *
	 * @throws
	*/
	BIA_EXPORT void pop(uint32_t _member_count);
	/**
	 * Pushes the variables to the stack.
	 *
	 * @since 3.65.132.734
	 * @date 30-Jun-18
	 *
	 * @param [in,out] _destination The destination of the created addresses.
	 * @param _member_count The amount of member variables.
	 *
	 * @throws 
	*/
	BIA_EXPORT void push(framework::member ** _destination, uint32_t _member_count);

private:
	/** The used memory allocator. */
	memory::allocator * _allocator;
	/** The base pointer of the stack. */
	int8_t * _buffer;
	/** The max size of the stack. */
	size_t _max_size;
	/** The current position of the stack pointer. */
	size_t _cursor;
};

}
}