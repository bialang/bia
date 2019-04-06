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
#include "name_manager.hpp"
#include "string_manager.hpp"
#include "regex.hpp"
#include "index_map.hpp"
#include "share_def.hpp"
#include "string_stream.hpp"
#include "function_holder.hpp"
#include "virtual_machine_code.hpp"
#include "parameter_setter.hpp"


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
	typedef uint32_t setup_count_t;
	typedef uint32_t regex_index_t;
	typedef uint32_t function_index_t;
	typedef stream::string_stream::length_t string_length_t;
	typedef std::vector<framework::member*> member_list_t;
	typedef std::vector<name_manager::name_t> name_list_t;

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
	/**
	 * Updates the globals list.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @param _member_map The member map.
	 *
	 * @throws See utility::index_map::to_list().
	*/
	BIA_EXPORT void set_member_map(const utility::index_map & _member_map);
	/**
	 * Updates the name list.
	 *
	 * @since 3.73.150.818
	 * @date 8-Mar-19
	 *
	 * @param _name_map The name map.
	 *
	 * @throws See utility::index_map::to_list().
	*/
	BIA_EXPORT void set_name_map(const utility::index_map & _name_map);
	BIA_EXPORT void set_setup_count(setup_count_t _count) noexcept;
	BIA_EXPORT setup_count_t setup_count() const noexcept;
	BIA_EXPORT regex_index_t register_regex_inplace(const uint8_t * _bytes, size_t _size);
	BIA_EXPORT regex_index_t register_regex_inplace(const char * _string, string_length_t _length);
	BIA_EXPORT regex_index_t register_regex_inplace(const char16_t * _string, string_length_t _length);
	BIA_EXPORT regex_index_t register_regex_inplace(const char32_t * _string, string_length_t _length);
	BIA_EXPORT function_index_t register_function_inplace(machine::virtual_machine::virtual_machine_code && _function_code);
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
	 * Returns the string manager.
	 *
	 * @since 3.73.150.816
	 * @date 24-Feb-19
	 *
	 * @return A reference to the string manager.
	*/
	BIA_EXPORT machine::string_manager & string_manager() noexcept;
	BIA_EXPORT std::vector<utility::share<detail::regex>> & regexs() noexcept;
	BIA_EXPORT std::vector<utility::share<detail::function_holder>> & functions() noexcept;
	/**
	 * Returns the globals list.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @return The global list.
	*/
	BIA_EXPORT const member_list_t & globals() const noexcept;
	/**
	 * Returns the name list.
	 *
	 * @since 3.73.150.818
	 * @date 8-Mar-19
	 *
	 * @return The name list.
	*/
	BIA_EXPORT const name_list_t & names() const noexcept;
	virtual_machine::parameter_setter & parameter_setter() noexcept
	{
		return _parameter_setter;
	}
	schein & operator=(schein && _right) noexcept = default;

protected:
	/** The linked context. */
	machine::machine_context * _context;
	/** The amount of temporary members needed at setup. */
	setup_count_t _setup_count;
	/** Stores all registered allocations with deleter. */
	std::vector<std::pair<memory::universal_allocation, deleter_function_t>> _allocations;
	/** Stores all registered regexs. */
	std::vector<utility::share<detail::regex>> _regexs;
	/** Stores all registered bia functions. */
	std::vector<utility::share<detail::function_holder>> _functions;
	/** The manager for the string resources. */
	machine::string_manager _string_manager;
	/** The globals list. */
	member_list_t _globals;
	/** The names. */
	name_list_t _names;
	/** The parameter setter that is responsible for the incoming parameters. */
	virtual_machine::parameter_setter _parameter_setter;
};

}
}