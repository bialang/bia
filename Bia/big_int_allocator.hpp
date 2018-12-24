#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include "config.hpp"
#include "allocator.hpp"
#include "big_int.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

typedef allocation<dependency::big_int> big_int_allocation;

/**
 * @brief Allocates memory for big ints.
 *
 * Allocates memory for big ints.
 *
 * @see @ref dependency::big_int
*/
class big_int_allocator
{
public:
	/** The size of a big int allocation in bytes. */
	constexpr static auto big_int_allocation_size = sizeof(dependency::big_int);

	/**
	 * Destructor.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	*/
	virtual ~big_int_allocator() = default;
	/**
	 * Initializes the big int library.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @param _allocator The memory allocator for normal purposes.
	 *
	 * @throws exception::argument_error If any arguments is invalid for initialization.
	*/
	BIA_EXPORT static void initialize(const std::shared_ptr<allocator> & _allocator);
	/**
	 * Deallocates the big int allocation.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @param _allocation The big int allocation.
	 *
	 * @throws exception::memory_error If the specified allocation wasn't allocated by allocate_big_int().
	*/
	virtual void deallocate_big_int(big_int_allocation _allocation) = 0;
	/**
	 * Destroys and deallocates the given big int.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @param _big_int The bit int.
	 *
	 * @throws See deallocate_big_int().
	 * @throws See dependency::big_int::~big_int().
	*/
	BIA_EXPORT void destroy_big_int(big_int_allocation _big_int);
	/**
	 * Allocates memory for one big int.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @throws exception::memory_error If no memory could be allocated.
	 *
	 * @return The allocated, but uninitialized big int.
	*/
	virtual big_int_allocation allocate_big_int() = 0;
	/**
	 * Allocates and constructs a big int with a specified initial value.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @tparam Arguments The types of the arguments passed to dependency::big_int::big_int().
	 *
	 * @param _value The arguments passed to the constructor of dependency::big_int::big_int().
	 *
	 * @throws See allocate_big_int().
	 * @throws See dependency::big_int::big_int().
	 *
	 * @return The constructed big int.
	*/
	template<typename... Arguments>
	big_int_allocation construct_big_int(Arguments &&... _arguments)
	{
		auto _big_int = allocate_big_int();

		new(_big_int) dependency::big_int(std::forward<Arguments>(_arguments)...);

		return _big_int;
	}

private:
	/** The normal memory allocator used for the underlying big int library. */
	static std::shared_ptr<allocator> _allocator;

	/**
	 * A memory function for the underlying big int library.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @param _ptr The buffer that should be freed.
	 * @param _size The size of the buffer.
	 *
	 * @throws See allocator::deallocate().
	*/
	BIA_EXPORT static void free(void * _ptr, size_t _size);
	/**
	 * A memory function for the underlying big int library.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @param _size The size of the allocated buffer.
	 *
	 * @throws See allocator::allocate().
	 *
	 * @return The allocated buffer.
	*/
	BIA_EXPORT static void * allocate(size_t _size);
	/**
	 * A memory function for the underlying big int library.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @param [in] _buffer The old buffer.
	 * @param _old_size The size of the buffer.
	 * @param _new_size The new size.
	 *
	 * @throws See allocator::reallocate().
	 *
	 * @return The reallocated buffer.
	*/
	BIA_EXPORT static void * reallocate(void * _buffer, size_t _old_size, size_t _new_size);
};

}
}
}