#pragma once

#include <cstdint>

#include "allocator.hpp"


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
	machine_stack(memory::allocator * _allocator, size_t _size);
	/**
	 * Destructor.
	 *
	 * @since 3.65.132.734
	 * @date 30-Jun-18
	 *
	 * @throws See memory::allocator::deallocate().
	*/
	~machine_stack();	
	/**
	 * Pops the variables from the stack.
	 *
	 * @since 3.65.132.734
	 * @date 30-Jun-18
	 *
	 * @param _member_count The amount of member variables.
	 * @param _address_count The amount of address variables.
	 *
	 * @throws
	*/
	void pop(uint32_t _member_count, uint32_t _address_count);
	/**
	 * Pushes the variables to the stack.
	 *
	 * @since 3.65.132.734
	 * @date 30-Jun-18
	 *
	 * @param _member_count The amount of member variables.
	 * @param _address_count The amount of address variables.
	 *
	 * @throws 
	 *
	 * @return The address of the allocated space.
	*/
	void * push(uint32_t _member_count, uint32_t _address_count);

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