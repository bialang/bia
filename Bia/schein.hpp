#pragma once

#include <cstdint>
#include <vector>
#include <functional>
#include <utility>

#include "config.hpp"
#include "allocator.hpp"
#include "member_allocator.hpp"
#include "executable_allocator.hpp"
#include "big_int_allocator.hpp"
#include "stack.hpp"
#include "string_manager.hpp"
#include "regex.hpp"
#include "share_def.hpp"


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
	typedef uint32_t regex_index_t;

	/**
	 * Constructor.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @param [in] _context The machine context.
	 *
	 * @throws See std::vector::vector().
	*/
	BIA_EXPORT schein(machine::machine_context & _context);
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
	BIA_EXPORT regex_index_t register_regex_inplace(const uint8_t * _bytes, size_t _size);
	BIA_EXPORT regex_index_t register_regex_inplace(const char * _string);
	BIA_EXPORT regex_index_t register_regex_inplace(const char16_t * _string);
	BIA_EXPORT regex_index_t register_regex_inplace(const char32_t * _string);
	/**
	 * Returns the machine context.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @return The linked machine context.
	*/
	BIA_EXPORT machine::machine_context * machine_context() noexcept;
	/**
	 * Returns the stack.
	 *
	 * @since 3.72.149.812
	 * @date 1-Feb-19
	 *
	 * @return A reference to the stack.
	*/
	BIA_EXPORT machine::stack & stack() noexcept;
	/**
	 * Returns the string manager.
	 *
	 * @since 3.73.150.816
	 * @date 24-Feb-19
	 *
	 * @return A reference to the string manager.
	*/
	BIA_EXPORT machine::string_manager & string_manager() noexcept;
	BIA_EXPORT std::vector<utility::share<dependency::regex>> & regexs() noexcept;
	schein & operator=(schein && _right) noexcept = default;

protected:
	/** The linked context. */
	machine::machine_context * _context;
	/** Stores all registered allocations with deleter. */
	std::vector<std::pair<memory::universal_allocation, deleter_function_t>> _allocations;
	/** Stores all registered regexs. */
	std::vector<utility::share<dependency::regex>> _regexs;
	/** The machine stack. */
	machine::stack _stack;
	/** The manager for the string resources. */
	machine::string_manager _string_manager;
};

}
}