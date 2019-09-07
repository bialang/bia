#pragma once

#include <cstddef>

namespace bia {
namespace gc {

/*
 The memory allocator base class. A memory allocator allocates aligned memory and is thread-safe.

 @see simple_allocator
*/
class memory_allocator
{
public:
	/* the alignment of the allocated memory */
	constexpr static std::size_t alignment = alignof(std::max_align_t);
	/* the alignment of the previous data */
	constexpr static std::size_t previous_data_alignment = 1;

	/*
	 Destructor.
	*/
	virtual ~memory_allocator() = default;

	/*
	 Deallocates the memory prior allocated by allocate(). This function is thread-safe to call.

	 @param ptr is the memory that should be freed
	 @param previous_size must be the same as during allocation, otherwise undefined behavior
	*/
	virtual void deallocate(void* ptr, std::size_t previous_size) = 0;
	/*
	 Allocates *size* bytes and returns the pointer to the first byte. This function is thread-safe to call. The memory is aligned according to memory_allocator::alignment.

	 @param size is the amount of required bytes
	 @param previous_size is the amount of bytes required before the first byte; this memory has an alignment of 1
	 @returns the pointer to the first byte if successful, otherwise `nullptr`
	*/
	virtual void* allocate(std::size_t size, std::size_t previous_size) = 0;
	/*
	 Calls allocate() and returns the non-null result. If allocate() returns `nullptr`, this function will throw a ...
	 
	 @param size is the amount of required bytes
	 @param previous_size is the amount of bytes required before the first byte; this memory has an alignment of 1
	 @returns the pointer to the first byte
	 @throws ... if the allocation failed
	 @todo add exception
	*/
	void* checked_allocate(std::size_t size, std::size_t previous_size)
	{
		auto ptr = allocate(size, previous_size);

		if (!ptr) {
		}

		return ptr;
	}
	/*
	 Checks whether the given integral is a power of 2.

	 @returns `true` if *x* is a power of 2, otherwise `false`
	*/
	static bool power_of_two(std::size_t x) noexcept
	{
		return !x && !(x & (x - 1));
	}
	/*
	 Sets the default memory allocator. This allocator must be created by `new` and will be automatically deleted by `delete`. This function is not thread-safe and it is dangerous to change the allocator after a default allocator was already acquired.

	 @param[in] allocator is the new default allocator
	*/
	static void default_allocator(memory_allocator* allocator) noexcept;
	/*
	 Returns the default memory allocator.

	 @returns the default memory allocator
	*/
	static memory_allocator* default_allocator() noexcept;
};

} // namespace gc
} // namespace bia