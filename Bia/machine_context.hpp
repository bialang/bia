#pragma once

#include <memory>
#include <utility>

#include "config.hpp"
#include "allocator.hpp"
#include "executable_allocator.hpp"
#include "input_stream.hpp"
#include "machine_code.hpp"
#include "string_key.hpp"
#include "member.hpp"
#include "string_manager.hpp"
#include "variable_index.hpp"
#include "machine_stack.hpp"


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
	 * @param _executable_allocator The allocator for executable memory.
	 *
	 * @throws exception::argument_error If the allocator is invalid.
	*/
	machine_context(const std::shared_ptr<memory::allocator> & _allocator, const std::shared_ptr<memory::executable_allocator> & _executable_allocator);
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _allocator The allocator for normal memory.
	 * @param _executable_allocator The allocator for executable memory.
	 *
	 * @throws exception::argument_error If the allocator is invalid.
	*/
	machine_context(std::shared_ptr<memory::allocator> && _allocator, std::shared_ptr<memory::executable_allocator> && _executable_allocator);
	void execute(stream::input_stream & _script)
	{
	}
	template<typename _Ty, typename... _Args>
	_Ty * emplace_member(const char * _name, _Args &&... _args)
	{
		auto _object = address_of_member(name_address(_name));

		_object->replace_this<_Ty>(std::forward<_Args>(_args)...);

		return static_cast<_Ty*>(_object);
	}
	/**
	 * Returns the currently active allocator of the current thread.
	 *
	 * @since 3.65.132.733
	 * @date 29-Jun-18
	 *
	 * @return The active allocator.
	*/
	static memory::allocator * active_allocator() noexcept;
	 /**
	  * Returns the memory allocator.
	  *
	  * @since 3.64.127.716
	  * @date 21-Apr-18
	  *
	  * @return The memory allocator of this context.
	 */
	memory::allocator * allocator() noexcept;
	/**
	 * Returns the memory allocator for executable memory.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @return The memory allocator of this context.
	*/
	memory::executable_allocator * executable_allocator() noexcept;
	machine::string_manager & string_manager() noexcept;

//private:


	/** The allocator of the context currently active. */
	static thread_local memory::allocator * _active_allocator;
	/** The allocator for normal memory. */
	const std::shared_ptr<memory::allocator> _allocator;
	/** The allocator for executable memory. */
	const std::shared_ptr<memory::executable_allocator> _executable_allocator;
	/** The string manager for string like resources. */
	machine::string_manager _string_manager;
	/** Holds all known variables, function and other. */
	variable_index _variable_index;
	/** The virtual machine stack. */
	machine_stack _stack;

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
	void BIA_MEMBER_CALLING_CONVENTION destroy_from_stack(uint32_t _member_count);
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
	void BIA_MEMBER_CALLING_CONVENTION create_on_stack(framework::member ** _destination, uint32_t _member_count);
	void BIA_MEMBER_CALLING_CONVENTION import(const char * _module);
	bool import(const char * _path, const char * _module);
	const char * name_address(utility::string_key _name);
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
	framework::member * address_of_member(const char * _name);
	machine_code compile_script(stream::input_stream & _script);
};

}
}
