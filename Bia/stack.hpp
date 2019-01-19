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
class stack
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
	BIA_EXPORT stack(memory::allocator * _allocator, size_t _size);
	stack(const stack & _copy) = delete;
	/**
	 * Move-Constructor.
	 *
	 * @since 3.68.140.788
	 * @date 16-Sep-18
	 *
	 * @param [in,out] _move The instance that should be moved.
	*/
	BIA_EXPORT stack(stack && _move) noexcept;
	/**
	 * Destructor.
	 *
	 * @since 3.65.132.734
	 * @date 30-Jun-18
	 *
	 * @throws See memory::allocator::deallocate().
	*/
	BIA_EXPORT ~stack();
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
	 * Recreates the last variables of the stack.
	 *
	 * @since 3.71.149.808
	 * @date 26-Dec-18
	 *
	 * @param _member_count The amount of member variables.
	 *
	 * @throws
	*/
	BIA_EXPORT void recreate(uint32_t _member_count);
	/**
	 * Recreates a range of variables of the stack.
	 *
	 * @since 3.71.149.808
	 * @date 26-Dec-18
	 *
	 * @param [in] _begin The beginning of the range. See push().
	 * @param _member_count The amount of the member variables.
	 *
	 * @throws
	*/
	BIA_EXPORT void recreate_range(framework::member * _begin, uint32_t _member_count);
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
	memory::allocation<int8_t> _buffer;
	/** The current position of the stack pointer. */
	size_t _cursor;
};

}
}