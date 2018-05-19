#pragma once

#include <memory>
#include <unordered_map>

#include "allocator.hpp"
#include "executable_allocator.hpp"
#include "stl_allocator_wrapper.hpp"
#include "input_stream.hpp"
#include "machine_code.hpp"
#include "string_key.hpp"
#include "member.hpp"
#include "string_manager.hpp"


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
	~machine_context()
	{

	}
	void execute(stream::input_stream & _script)
	{ }
	/**
	 * Returns the memory allocator.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @return The memory allocator of this context.
	*/
	memory::allocator * get_allocator() noexcept;
	/**
	 * Returns the memory allocator for executable memory.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @return The memory allocator of this context.
	*/
	memory::executable_allocator * get_executable_allocator() noexcept;

//private:
	/** The allocator for normal memory. */
	std::shared_ptr<memory::allocator> _allocator;
	/** The allocator for executable memory. */
	std::shared_ptr<memory::executable_allocator> _executable_allocator;
	/** Holds all known variables, function and other. */
	std::unordered_map<utility::string_key, std::unique_ptr<framework::member>, utility::string_key::hasher> _variable_index;
	//std::unordered_map<utility::string_key, std::unique_ptr<framework::member>, utility::string_key::hasher, std::equal_to<utility::string_key>, memory::stl_allocator_wrapper<std::pair<const utility::string_key, std::unique_ptr<framework::member>>>> _variable_index;
	/** The string manager for string like resources. */
	string_manager _string_manager;


	framework::member * get_address_or_create(const utility::string_key & _name);
	machine_code compile_script(stream::input_stream & _script);
};

}
}