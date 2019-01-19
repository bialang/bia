#pragma once

#include <vector>
#include <functional>
#include <utility>

#include "config.hpp"
#include "allocator.hpp"
#include "executable_allocator.hpp"
#include "big_int_allocator.hpp"


namespace bia
{
namespace machine
{

/**
 * @brief Contains information about the code.
 *
 * @see @ref code
*/
class schein
{
public:
	/** The deleter function signature. */
	typedef std::function<void(memory::universal_allocation)> deleter_function_t;

	/**
	 * Constructor.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @param [in] _allocator The memory allocator.
	 * @param [in] _executable_allocator The executable memory allocator.
	 * @param [in] _big_int_allocator The big int allocator.
	 *
	 * @throws See std::vector::vector().
	*/
	BIA_EXPORT schein(memory::allocator * _allocator, memory::executable_allocator * _executable_allocator, memory::big_int_allocator * _big_int_allocator);
	schein(const schein & _copy) = delete;
	schein(schein && _move) noexcept = default;
	/**
	 * Destructor.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @throws See clear().
	*/
	BIA_EXPORT virtual ~schein();
	/**
	 * Registers an allocation.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @param _allocation The allocation.
	 * @param _deleter (Optional) If the deleter is not given, the allocation will be deleted with allocator().
	 *
	 * @throws See std::vector::emplace_back().
	*/
	BIA_EXPORT void register_allocation(memory::universal_allocation _allocation, deleter_function_t && _deleter = {});
	/**
	 * Registers an allocation.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @param _allocation The allocation.
	 * @param _deleter Deletes the allocation.
	 *
	 * @throws See std::vector::emplace_back().
	*/
	BIA_EXPORT void register_allocation(memory::universal_allocation _allocation, const deleter_function_t & _deleter);
	/**
	 * Registers a big int.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @param _allocation The big int allocation.
	 *
	 * @throws See register_allocation().
	*/
	BIA_EXPORT void register_big_int(memory::big_int_allocation _allocation);
	/**
	 * Clears all allocations.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @param param_des
	 *
	 * @throws See the @a _deleter function of register_allocation().
	 * @throws See memory::allocator::deallocate() and memory::big_int_allocator::destroy_big_int().
	 * @throws See std::vector::clear().
	*/
	BIA_EXPORT void clear();
	/**
	 * Returns ths memory allocator.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @return The memory allocator.
	*/
	BIA_EXPORT memory::allocator * allocator() noexcept;
	/**
	 * Returns the executable memory allocator.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @return The executable memory allocator.
	*/
	BIA_EXPORT memory::executable_allocator * executable_allocator() noexcept;

protected:
	/** The memory allocator for normal memory. */
	memory::allocator * _allocator;
	/** The memory allocator for executable memory. */
	memory::executable_allocator * _executable_allocator;
	/** The memory allocator for big ints. */
	memory::big_int_allocator * _big_int_allocator;
	/** Stores all registered allocations with deleter. */
	std::vector<std::pair<memory::universal_allocation, deleter_function_t>> _allocations;
};

}
}