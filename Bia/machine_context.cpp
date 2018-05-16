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

machine_context::machine_context(const std::shared_ptr<memory::allocator>& _allocator, const std::shared_ptr<memory::executable_allocator>& _executable_allocator) : _allocator(_allocator), _executable_allocator(_executable_allocator), _string_manager(this->_allocator.get())
{
	if (!this->_allocator || !this->_executable_allocator) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
}

machine_context::machine_context(std::shared_ptr<memory::allocator>&& _allocator, std::shared_ptr<memory::executable_allocator>&& _executable_allocator) : _allocator(std::move(_allocator)), _executable_allocator(std::move(_executable_allocator)), _string_manager(this->_allocator.get())
{
	if (!this->_allocator || !this->_executable_allocator) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
}

memory::allocator * machine_context::get_allocator() noexcept
{
	return _allocator.get();
}

memory::executable_allocator * machine_context::get_executable_allocator() noexcept
{
	return _executable_allocator.get();
}

framework::member * machine_context::get_address_or_create(const utility::string_key & _name)
{
	auto _result = _variable_index.find(_name);

	// Create
	if (_result == _variable_index.end()) {
		auto _allocation = _allocator->construct_blocks<framework::member, framework::undefined_member>(1);

		return _variable_index.emplace(_name, std::unique_ptr<framework::member>(_allocation.first)).first->second.get();
	}

	return _result->second.get();
}

framework::member * machine_context::get_address_or_create(utility::string_key && _name)
{
	static framework::undefined_member a;
	return &a;
	auto _result = _variable_index.find(_name);

	// Create
	if (_result == _variable_index.end()) {
		auto _allocation = _allocator->construct_blocks<framework::member, framework::undefined_member>(1);

		return _variable_index.emplace(std::move(_name), std::unique_ptr<framework::member>(_allocation.first)).first->second.get();
	}

	return _result->second.get();
}

machine_code machine_context::compile_script(stream::input_stream & _script)
{
	// Create compiler
	stream::buffer_output_stream _output;
	compiler::compiler _compiler(_output, *this);

	// Interpret
	grammar::syntax::get_interpreter().interpret(_script, _compiler);

	_compiler.finalize();

	return _compiler.get_code();
}


}
}