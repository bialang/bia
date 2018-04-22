#pragma once

#include <memory>

#include "allocator.hpp"
#include "input_stream.hpp"
#include "machine_code.hpp"


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
	 * @param _allocator The memory allocator.
	 *
	 * @throws exception::argument_error If the allocator is invalid.
	*/
	machine_context(std::shared_ptr<memory::allocator> _allocator);
	~machine_context();
	void execute(stream::input_stream & _script);
	/**
	 * Returns the memory allocator.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @return The memory allocator of this context.
	*/
	memory::allocator * get_allocator() noexcept;

private:
	/** The memory allocator. */
	std::shared_ptr<memory::allocator> _allocator;


	machine_code compile_script(stream::input_stream & _script);
};

}
}