#pragma once

#include <cstddef>
#include <utility>
#include <cstdint>

#include "config.hpp"
#include "exception.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

typedef size_t size_type;

/** An allocation with type. */
template<typename Type>
class allocation
{
public:
	Type * first;
	size_type second;

	allocation() noexcept
	{
		clear();
	}
	allocation(Type * _first, size_type _second) noexcept
	{
		first = _first;
		second = _second;
	}
	allocation(const allocation & _copy) noexcept = default;
	allocation(allocation && _move) noexcept
	{
		first = _move.first;
		second = _move.second;

		_move.clear();
	}
	void clear() noexcept
	{
		first = nullptr;
		second = 0;
	}
	operator bool() const noexcept
	{
		return first != nullptr;
	}
	operator Type*() noexcept
	{
		return first;
	}
	operator const Type*() const noexcept
	{
		return first;
	}
	Type * operator->() noexcept
	{
		return first;
	}
	const Type * operator->() const noexcept
	{
		return first;
	}
	Type ** operator&() noexcept
	{
		return &first;
	}
	Type * const* operator&() const noexcept
	{
		return &first;
	}
	allocation & operator=(const allocation & _copy) noexcept = default;
	allocation & operator=(allocation && _move) noexcept
	{
		first = _move.first;
		second = _move.second;

		_move.clear();

		return *this;
	}
};

/** An universal allocation. */
typedef allocation<void> universal_allocation;


/**
 * Casts an allocation to the defined type.
 *
 * @since 3.64.127.716
 * @date 7-Apr-18
 *
 * @tparam Cast_type The wanted type.
 * @tparam Type The passed type.
 *
 * @param _allocation Defines the allocation.
 *
 * @return The cast allocation.
*/
template<typename Cast_type, typename Type>
inline allocation<Cast_type> cast_allocation(allocation<Type> _allocation) noexcept
{
	return { static_cast<Cast_type*>(_allocation.first), _allocation.second };
}

/**
 * @brief An allocator interface.
 *
 * An interface for allocating memory.
 *
 * @see @ref simple_allocator
*/
class allocator
{
public:
	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	*/
	virtual ~allocator() noexcept = default;
	/**
	 * Destroys and deallocates the element created by construct().
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @tparam Base The returned type.
	 * @tparam Deriviate The constructed type.
	 *
	 * @param _allocation The allocation.
	 *
	 * @throws See deallocate().
	 * @throws See the destructor of @a Deriviate.
	*/
	template<typename Base, typename Deriviate = Base>
	void destroy(allocation<Base> _allocation)
	{
		// Destroy element
		if (_allocation) {
			_allocation.first->~Deriviate();

			deallocate(cast_allocation<void>(_allocation));
		}
	}
	/**
	 * Destroys and deallocates the blocks created by allocate_blocks().
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @tparam Type The allocation type.
	 *
	 * @param _allocation The allocation.
	 *
	 * @throws See deallocate_blocks().
	 * @throws See the destructor of @a _Ty.
	*/
	template<typename Type>
	void destroy_blocks(allocation<Type> _allocation)
	{
		auto _ptr = reinterpret_cast<int8_t*>(_allocation.first);
		auto _block_size = block_size();

		// Destroy all elements
		for (size_type i = 0; i < _allocation.second; ++i) {
			reinterpret_cast<Type*>(_ptr + i * _block_size)->~Type();
		}

		deallocate_blocks(cast_allocation<void>(_allocation));
	}
	/**
	 * Deallocates the allocation allocated by allocate().
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _allocation The allocation.
	 *
	 * @throws exception::memory_error If the specified allocation is invalid.
	*/
	virtual void deallocate(universal_allocation _allocation) = 0;
	/**
	 * Deallocates the blocks allocated by allocate_blocks().
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _blocks The allocation.
	 *
	 * @throws exception::memory_error If the specified allocation is invalid.
	*/
	virtual void deallocate_blocks(universal_allocation _blocks) = 0;
	/**
	 * Returns the required block size.
	 *
	 * @since 3.64.132.731
	 * @date 28-Jun-18
	 *
	 * @return The block size.
	*/
	BIA_EXPORT static size_t block_size() noexcept;
	/**
	 * Can be used to expand or shrinken an allocation.
	 *
	 * @remarks If a new memory is allocated, the data will be copied.
	 *
	 * @since 3.65.134.742
	 * @date 2-Aug-18
	 *
	 * @param _allocation The allocation that should be expanded or shrinken.
	 * @param _size The new size.
	 *
	 * @throws exception::memory_error If the memory could not be allocated.
	 *
	 * @return The reallocated allocation.
	*/
	virtual universal_allocation reallocate(universal_allocation _allocation, size_type _size) = 0;
	/**
	 * Commits the memory reserved by prepare().
	 *
	 * @remarks The returned allocation can have the same size as @a _allocation.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _allocation The allocation.
	 * @param _size The final size of the allocation.
	 *
	 * @throws exception::memory_error If the specified allocation or the size are invalid.
	 *
	 * @return The allocation with possibly adapted size parameter.
	*/
	virtual universal_allocation commit(universal_allocation _allocation, size_type _size) = 0;
	/**
	 * Allocates memory.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _size The size of the allocation in bytes.
	 *
	 * @throws exception::memory_error If the memory could not be allocated.
	 *
	 * @return The allocation.
	*/
	virtual universal_allocation allocate(size_type _size) = 0;
	/**
	 * Allocates the specified amount of blocks.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _count The amount of the blocks.
	 *
	 * @throws exception::memory_error If the memory could not be allocated.
	 *
	 * @return The blocks.
	*/
	virtual universal_allocation allocate_blocks(size_type _count) = 0;
	/**
	 * Prepares memory if the actual size can be smaller.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _size The maximum size of the allocation.
	 *
	 * @throws exception::memory_error If the memory could not be allocated.
	 *
	 * @return The allocation.
	 *
	 * @see For commiting the actual size use commit().
	*/
	virtual universal_allocation prepare(size_type _size) = 0;
	/**
	 * Allocates and constructs the desired type.
	 *
	 * @remarks @a _Deriviate must inherit @a _Base.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @tparam Base The returned type.
	 * @tparam Deriviate The constructed type.
	 * @tparam Arguments The arguments that will be used to construct the element.
	 *
	 * @param _arguments The arguments used to create the element.
	 *
	 * @throws See allocate().
	 * @throws See the constructor of @a Deriviate.
	 *
	 * @return The allocated and constructed block.
	*/
	template<typename Base, typename Deriviate = Base, typename... Arguments>
	allocation<Base> construct(Arguments &&... _arguments)
	{
		auto _allocation = allocate(sizeof(Deriviate));

		// Construct element
		new(_allocation.first) Deriviate(std::forward<Arguments>(_arguments)...);

		return cast_allocation<Base>(_allocation);
	}
	/**
	 * Allocates and constructs blocks of the desired type.
	 *
	 * @remarks @a _Deriviate must inherit @a _Base and must be smaller than @ref block_size.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @tparam Base The returned type.
	 * @tparam Deriviate The constructed type.
	 * @tparam Arguments The arguments that will be used to construct the blocks.
	 *
	 * @param _count How many blocks should be constructed.
	 * @param _arguments The arguments used to create the blocks.
	 *
	 * @throws See allocate_blocks().
	 * @throws See the constructor of @a Deriviate.
	 *
	 * @return The allocated blocks.
	*/
	template<typename Base, typename Deriviate = Base, typename... Arguments>
	allocation<Base> construct_blocks(size_type _count, Arguments &&... _arguments)
	{
		auto _block_size = block_size();

		if (sizeof(Deriviate) > _block_size) {
			throw BIA_IMPLEMENTATION_EXCEPTION("Elements exceeds block size.");
		}

		auto _allocation = allocate_blocks(_count);
		auto _ptr = static_cast<int8_t*>(_allocation.first);

		// Construct all elements
		for (size_type i = 0; i < _count; ++i) {
			new(_ptr + i * _block_size) Deriviate(std::forward<Arguments>(_arguments)...);
		}

		return cast_allocation<Base>(_allocation);
	}

};

}
}
}
