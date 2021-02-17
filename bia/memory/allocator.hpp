#ifndef BIA_MEMORY_ALLOCATOR_HPP_
#define BIA_MEMORY_ALLOCATOR_HPP_

#include <bia/error/exception.hpp>
#include <bia/util/gsl.hpp>
#include <cstddef>
#include <new>
#include <utility>

namespace bia {
namespace memory {

/// The memory allocator base class. A memory allocator allocates aligned memory and is thread-safe.
class Allocator
{
public:
	/// The alignment of the allocated memory.
	constexpr static std::size_t alignment = alignof(std::max_align_t);

	virtual ~Allocator() = default;
	/// Deallocates the memory prio allocated by allocate(). If the pointer is null, this operation is a noop.
	virtual void deallocate(void* ptr) = 0;
	/**
	 * Allocates at least *size* bytes of uninitialized memory and returns the pointer to the first byte. This
	 * function is thread-safe to call. The memory is aligned according to memory_allocator::alignment.
	 *
	 * @param size is the amount of required bytes
	 * @return the pointer to the first byte if successful, otherwise `nullptr`
	 */
	virtual void* allocate(std::size_t size) = 0;
	/**
	 * Calls allocate() and returns the non-null result. If allocate() returns `nullptr`, this function will
	 * fail.
	 *
	 * @exception error::exception
	 * 	- std::errc::not_enough_memory if no more memory could be allocated
	 * @param size is the amount of required bytes
	 * @return the pointer to the first byte
	 */
	util::Not_null<void*> checked_allocate(std::size_t size)
	{
		const auto ptr = allocate(size);
		if (!ptr) {
			BIA_THROW(std::make_error_code(std::errc::not_enough_memory));
		}
		return ptr;
	}
	template<typename Type, typename... Arguments>
	Type* construct(Arguments&&... arguments)
	{
		return new (checked_allocate(sizeof(Type)).get()) Type{ std::forward<Arguments>(arguments)... };
	}
	template<typename Type>
	void destroy(Type* object)
	{
		object->~Type();
		deallocate(object);
	}
};

} // namespace memory
} // namespace bia

#endif
