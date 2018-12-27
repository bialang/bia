#pragma once

#include <memory>
#include <utility>

#include "config.hpp"
#include "allocator.hpp"
#include "member_allocator.hpp"
#include "big_int_allocator.hpp"
#include "executable_allocator.hpp"
#include "input_stream.hpp"
#include "machine_code.hpp"
#include "string_key.hpp"
#include "member.hpp"
#include "string_manager.hpp"
#include "variable_index.hpp"
#include "machine_stack.hpp"
#include "module_loader.hpp"
#include "buffer_builder.hpp"


namespace bia
{
namespace machine
{

/**
 * @brief A Bia machine context.
 *
 * A machine context is used to store compiled script, execute them and store everything a script uses and knows. For example: global variables, modules and set function or classes. A context is not thread safe, however, read-only actions are.
*/
class machine_context final
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _allocator The allocator for normal memory.
	 * @param _member_allocator The member allocator.
	 * @param _big_int_allocator The big int allocator.
	 * @param _executable_allocator The allocator for executable memory.
	 *
	 * @throws exception::argument_error If the allocator is invalid.
	*/
	BIA_EXPORT machine_context(const std::shared_ptr<memory::allocator> & _allocator, const std::shared_ptr<memory::member_allocator> & _member_allocator, const std::shared_ptr<memory::big_int_allocator> & _big_int_allocator, const std::shared_ptr<memory::executable_allocator> & _executable_allocator);
	machine_context(const machine_context & _copy) = delete;
	machine_context(machine_context && _move) = default;
	/**
	 * Activates the current context.
	 *
	 * @since 3.68.138.786
	 * @date 15-Sep-18
	*/
	BIA_EXPORT void activate_context() noexcept;
	void execute(stream::input_stream & _script)
	{
		BIA_NOT_IMPLEMENTED;
	}
	void add_script(const char * _name, stream::input_stream & _script)
	{
		BIA_NOT_IMPLEMENTED;
	}
	const machine_code & get_script(const char * _name)
	{
		BIA_NOT_IMPLEMENTED;
	}
	template<typename Member, typename... Arguments>
	Member * emplace_member(const char * _name, Arguments &&... _arguments)
	{
		auto _object = address_of_member(name_address(_name));

		_object->replace_this<Member>(std::forward<Arguments>(_arguments)...);

		return static_cast<Member*>(_object);
	}
	/**
	 * Returns the currently active machine context in the current thread.
	 *
	 * @since 3.68.138.786
	 * @date 15-Sep-18
	 *
	 * @return The active context or null if there is no active context.
	*/
	BIA_EXPORT static machine_context * active_context() noexcept;
	/**
	 * Returns the currently active allocator of the current thread.
	 *
	 * @since 3.65.132.733
	 * @date 29-Jun-18
	 *
	 * @return The active allocator or null if there is no active allocator.
	*/
	BIA_EXPORT static memory::allocator * active_allocator() noexcept;
	/**
	 * Returns the currently active member allocator of the current thread.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @return The active member allocator or null if there is no active allocator.
	*/
	BIA_EXPORT static memory::member_allocator * active_member_allocator() noexcept;
	/**
	 * Returns the currently active big int allocator of the current thread.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @return The active member big int or null if there is no active allocator.
	*/
	BIA_EXPORT static memory::big_int_allocator * active_big_int_allocator() noexcept;
	BIA_EXPORT static utility::buffer_builder * active_buffer_builder() noexcept;
	 /**
	  * Returns the memory allocator.
	  *
	  * @since 3.64.127.716
	  * @date 21-Apr-18
	  *
	  * @return The memory allocator of this context.
	 */
	BIA_EXPORT memory::allocator * allocator() noexcept;
	/**
	 * Returns the member allocator.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @return The member allocator of this context.
	*/
	BIA_EXPORT memory::member_allocator * member_allocator() noexcept;
	/**
	 * Returns the big int allocator.
	 *
	 * @since 3.68.141.793
	 * @date 2-Dec-18
	 *
	 * @return The big int allocator of this context.
	*/
	BIA_EXPORT memory::big_int_allocator * big_int_allocator() noexcept;
	/**
	 * Returns the memory allocator for executable memory.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @return The memory allocator of this context.
	*/
	BIA_EXPORT memory::executable_allocator * executable_allocator() noexcept;
	BIA_EXPORT utility::buffer_builder & buffer_builder() noexcept;
	BIA_EXPORT machine::string_manager & string_manager() noexcept;

//private:


	/** The active context in the current thread. */
	static thread_local machine_context * _active_context;
	/** The allocator of the context currently active. */
	static thread_local memory::allocator * _active_allocator;
	/** The member allocator of the currently active context. */
	static thread_local memory::member_allocator * _active_member_allocator;
	/** The active big int allocator. */
	static thread_local memory::big_int_allocator * _active_big_int_allocator;
	static thread_local utility::buffer_builder * _active_buffer_builder;
	/** The allocator for normal memory. */
	const std::shared_ptr<memory::allocator> _allocator;
	/** The member allocator of the context. */
	const std::shared_ptr<memory::member_allocator> _member_allocator;
	/** The big int allocator of the context. */
	const std::shared_ptr<memory::big_int_allocator> _big_int_allocator;
	/** The allocator for executable memory. */
	const std::shared_ptr<memory::executable_allocator> _executable_allocator;
	utility::buffer_builder _buffer_builder;
	/** The string manager for string like resources. */
	machine::string_manager _string_manager;
	/** Holds all known variables, function and other. */
	variable_index _variable_index;
	/** The virtual machine stack. */
	machine_stack _stack;
	/** The module loader. */
	modular::module_loader _module_loader;

	/**
	 * Pops the variables from the stack.
	 *
	 * @since 3.65.132.734
	 * @date 30-Jun-18
	 *
	 * @param _member_count The amount of member variables.
	 *
	 * @throws See machine_stack::pop().
	*/
	BIA_EXPORT void BIA_MEMBER_CALLING_CONVENTION destroy_from_stack(uint32_t _member_count);
	/**
	 * Recreates the last variables of the stack.
	 *
	 * @since 3.71.149.808
	 * @date 26-Dec-18
	 *
	 * @param _member_count The amount of member variables.
	 *
	 * @throws See machine_stack::recreate().
	*/
	BIA_EXPORT void BIA_MEMBER_CALLING_CONVENTION recreate_on_stack(uint32_t _member_count);
	/**
	 * Recreates a range of variables of the stack.
	 *
	 * @since 3.71.149.808
	 * @date 26-Dec-18
	 *
	 * @param _begin The beginning of the range.
	 * @param _member_count The amount of member variables.
	 *
	 * @throws See machine_stack::recreate_range().
	*/
	BIA_EXPORT void BIA_MEMBER_CALLING_CONVENTION recreate_range_on_stack(framework::member * _begin, uint32_t _member_count);
	/**
	 * Pushes the variables to the stack.
	 *
	 * @since 3.65.132.734
	 * @date 30-Jun-18
	 *
	 * @param [in,out] _destination The destination of the created addresses.
	 * @param _member_count The amount of member variables.
	 *
	 * @throws See machine_stack::push().
	 *
	 * @return The address of the allocated space.
	*/
	BIA_EXPORT void BIA_MEMBER_CALLING_CONVENTION create_on_stack(framework::member ** _destination, uint32_t _member_count);
	BIA_EXPORT void BIA_MEMBER_CALLING_CONVENTION import_module(const char * _name);
	BIA_EXPORT const char * name_address(utility::string_key _name);
	/**
	 * Returns the member address of the key. If it does not exists, it will be created.
	 *
	 * @since 3.64.131.725
	 * @date 19-May-18
	 *
	 * @param _name The key.
	 *
	 * @throws See variable_index::find() and variable_index::add().
	 *
	 * @return The member address.
	*/
	BIA_EXPORT framework::member * address_of_member(const char * _name);
	BIA_EXPORT machine_code compile_script(stream::input_stream & _script);
};

}
}
