#ifndef BIA_GC_MEMORY_ALLOCATOR_HPP_
#define BIA_GC_MEMORY_ALLOCATOR_HPP_

#include <cstddef>
#include <bia/exception/memory_error.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace gc {
namespace memory {

/**
 * The memory allocator base class. A memory allocator allocates aligned memory and is thread-safe.
 *
 * @see simple_allocator
 */
class allocator
{
public:
	/** the alignment of the allocated memory */
	constexpr static std::size_t alignment = alignof(std::max_align_t);

	/*
	 Destructor.
	*/
	virtual ~allocator() = default;
	/**
	 * Deallocates the memory prior allocated by allocate(). This function is thread-safe to call.
	 *
	 * @pre `ptr` was allocated by allocate() or checked_allocated() and not deallocated before
	 *
	 * @param ptr is the memory that should be freed; if equal to `nullptr` this operation is a noop
	 * @param previous_size must be the same as during allocation, otherwise undefined behavior
	 */
	virtual void deallocate(void* ptr) = 0;
	/**
	 * Allocates *size* bytes and returns the pointer to the first byte. This function is thread-safe to call.
	 * The memory is aligned according to memory_allocator::alignment.
	 *
	 * @param size is the amount of required bytes
	 * @returns the pointer to the first byte if successful, otherwise `nullptr`
	 */
	virtual void* allocate(std::size_t size) = 0;
	/**
	 * Calls allocate() and returns the non-null result. If allocate() returns `nullptr`, this function will
	 * fail.
	 *
	 * @param size is the amount of required bytes
	 * @returns the pointer to the first byte
	 * @throw exception::memory_error if the allocation failed
	 */
	util::not_null<void*> checked_allocate(std::size_t size)
	{
		auto ptr = allocate(size);

		if (!ptr) {
			BIA_THROW(exception::memory_error, "could not allocate more memory");
		}

		return ptr;
	}
	/**
	 * Checks whether the given integral is a power of 2.
	 *
	 * @returns `true` if *x* is a power of 2, otherwise `false`
	 */
	constexpr static bool power_of_two(std::size_t x) noexcept
	{
		return !x && !(x & (x - 1));
	}
};

} // namespace memory
} // namespace gc
} // namespace bia

#endif
