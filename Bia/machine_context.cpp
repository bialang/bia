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

thread_local memory::allocator * machine_context::_active_allocator = nullptr;


machine_context::machine_context(const std::shared_ptr<memory::allocator>& _allocator, const std::shared_ptr<memory::executable_allocator>& _executable_allocator) : _allocator(_allocator), _executable_allocator(_executable_allocator), _string_manager(this->_allocator.get()), _variable_index(this->_allocator)
{
	if (!this->_allocator || !this->_executable_allocator) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
}

machine_context::machine_context(std::shared_ptr<memory::allocator>&& _allocator, std::shared_ptr<memory::executable_allocator>&& _executable_allocator) : _allocator(std::move(_allocator)), _executable_allocator(std::move(_executable_allocator)), _string_manager(this->_allocator.get()), _variable_index(this->_allocator)
{
	if (!this->_allocator || !this->_executable_allocator) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
}

memory::allocator * machine_context::get_active_allocator() noexcept
{
	return _active_allocator;
}

memory::allocator * machine_context::get_allocator() noexcept
{
	return _allocator.get();
}

memory::executable_allocator * machine_context::get_executable_allocator() noexcept
{
	return _executable_allocator.get();
}

const char * machine_context::get_name_address(utility::string_key _name)
{
	return _string_manager.get_name_address(_name.get_string(), _name.length());
}

framework::member * machine_context::get_address_or_create(const char * _name)
{
	if (auto _result = _variable_index.find(_name)) {
		return _result;
	}

	// Create
	auto _allocation = _allocator->construct_blocks<framework::member, framework::undefined_member>(1);
	auto a = _variable_index.add(_name, _allocation);
	printf("created: %p\n", a);
	return a;
}

machine_code machine_context::compile_script(stream::input_stream & _script)
{
	// Create compiler
	stream::buffer_output_stream _output;
	compiler::compiler _compiler(_output, *this);

	// Interpret
	grammar::syntax::get_interpreter().interpret(_script, _compiler, *this);

	_compiler.finalize();

	return _compiler.get_code();
}


}
}