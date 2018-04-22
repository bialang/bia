#include "machine_context.hpp"
#include "exception.hpp"
#include "compiler.hpp"
#include "syntax.hpp"
#include "buffer_output_stream.hpp"


namespace bia
{
namespace machine
{

machine_context::machine_context(std::shared_ptr<memory::allocator> _allocator) : _allocator(std::move(_allocator))
{
	if (!this->_allocator.get()) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
}

memory::allocator * machine_context::get_allocator() noexcept
{
	return _allocator.get();
}

machine_code machine_context::compile_script(stream::input_stream & _script)
{
	// Create compiler
	stream::buffer_output_stream _output;
	compiler::compiler _compiler(_output);

	// Interpret
	grammar::syntax::get_interpreter().interpret(_script, _compiler);

	_compiler.finalize();

	return _compiler.get_code();
}


}
}