#include "machine_context.hpp"
#include "exception.hpp"
#include "compiler.hpp"
#include "syntax.hpp"
#include "buffer_output_stream.hpp"
#include "undefined_member.hpp"


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

framework::member * machine_context::get_address_or_create(const utility::string_key & _name)
{
	auto _result = _variable_index.find(_name);

	// Create
	if (_result == _variable_index.end()) {
		;
		return _variable_index.emplace(_name, std::unique_ptr<framework::member>(_allocator->construct_blocks<framework::undefined_member>(1, memory::allocator::MEMORY_TYPE::NORMAL).
			)).first->second.get();
	}

	return _result->second.get();
}

framework::member * machine_context::get_address_or_create(utility::string_key && _name)
{
	auto _result = _variable_index.find(_name);

	// Create
	if (_result == _variable_index.end()) {
		return _variable_index.emplace(std::move(_name), std::unique_ptr<framework::member>(new framework::undefined_member())).first->second.get();
	}

	return _result->second.get();
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