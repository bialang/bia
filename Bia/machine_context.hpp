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
#include "script_map.hpp"
#include "static_function.hpp"
#include "lambda_function_def.hpp"


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
	 * Destructor.
	 *
	 * @since 3.71.149.809
	 * @date 29-Dec-18
	 *
	 * @throws
	*/
	BIA_EXPORT ~machine_context();
	/**
	 * Activates the current context.
	 *
	 * @since 3.68.138.786
	 * @date 15-Sep-18
	*/
	BIA_EXPORT void activate_context() noexcept;
	/**
	 * Sets all active components to null.
	 *
	 * @since 3.71.149.809
	 * @date 29-Dec-18
	*/
	BIA_EXPORT static void unset_active_context() noexcept;
	/**
	 * Compiles and executes the given script.
	 *
	 * @since 3.71.149.809
	 * @date 28-Dec-18
	 *
	 * @param [in] _script The script.
	 *
	 * @throws See compile_script().
	 * @throws See machine_code::execute().
	*/
	BIA_EXPORT void execute(stream::input_stream & _script);
	/**
	 * Compiles and adds a script to the context.
	 *
	 * @since 3.71.149.809
	 * @date 29-Dec-18
	 *
	 * @param _name The name of the script.
	 * @param [in] _script The script.
	 *
	 * @throws See compile_script().
	 * @throws See script_map::set().
	*/
	BIA_EXPORT void add_script(const char * _name, stream::input_stream & _script);
	/**
	 * Returns the script associated with the name.
	 *
	 * @since 3.71.149.809
	 * @date 29-Dec-18
	 *
	 * @param _name The name of the script.
	 *
	 * @throws See script_map::get().
	 *
	 * @return A reference to the script.
	*/
	BIA_EXPORT const machine_code & get_script(const char * _name) const;
	/**
	 * Returns the none pointer.
	 *
	 * @since 3.71.149.809
	 * @date 29-Dec-18
	 *
	 * @return The none pointer. See get_member().
	*/
	static framework::member * none() noexcept
	{
		return reinterpret_cast<framework::member*>(-1);
	}
	/**
	 * Returns the member.
	 *
	 * @since 3.71.149.809
	 * @date 28-Dec-18
	 *
	 * @param _name The name of the member.
	 * @param _default The default return value if the member was not found. If set to @a none, an exception will be thrown instead.
	 *
	 * @throws exception::symbol_error If the value is not found and the @a _default value is set to none().
	 *
	 * @return The member if it exists, otherwise the @a _default value.
	*/
	BIA_EXPORT framework::member * get_member(string_manager::name_t, framework::member * _default = none());
	/**
	 * Returns the member.
	 *
	 * @since 3.71.149.809
	 * @date 28-Dec-18
	 *
	 * @param _name The name of the member.
	 * @param _default The default return value if the member was not found. If set to @a none, an exception will be thrown instead.
	 *
	 * @throws exception::symbol_error If the value is not found and the @a _default value is set to none().
	 *
	 * @return The member if it exists, otherwise the @a _default value.
	*/
	BIA_EXPORT const framework::member * get_member(string_manager::name_t, framework::member * _default = none()) const;
	template<typename Member, typename... Arguments>
	typename std::enable_if<std::is_base_of<framework::member, Member>::value, Member*>::type emplace_member(const char * _name, Arguments &&... _arguments)
	{
		activate_context();

		auto _object = address_of_member(name_address(_name));

		_object->template replace_this<Member>(std::forward<Arguments>(_arguments)...);

		return static_cast<Member*>(_object);
	}
	template<typename Return, typename... Arguments>
	framework::executable::static_function<Return, Arguments...> * set_function(string_manager::name_t _name, Return(*_function)(Arguments...))
	{
		return emplace_member<framework::executable::static_function<Return, Arguments...>>(_name, _function);
	}
	template<typename _Lambda>
	framework::executable::lambda_function<typename std::remove_cv<typename std::remove_reference<_Lambda>::type>::type> * set_lambda(string_manager::name_t _name, _Lambda && _lambda)
	{
		return emplace_member<framework::executable::lambda_function<typename std::remove_cv<typename std::remove_reference<_Lambda>::type>::type>>(_name, std::forward<_Lambda>(_lambda));
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

private:
	friend compiler::compiler;
	template<typename Type, typename Class>
	friend class framework::object::template_wrapper;
	friend grammar::interpreter_token;
	friend disassembler;
	friend platform::x86_toolset;

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
	/** The script map. */
	script_map _script_map;
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
