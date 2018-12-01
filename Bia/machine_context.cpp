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

thread_local machine_context * machine_context::_active_context = nullptr;
thread_local machine_context::member_allocator * machine_context::_active_allocator = nullptr;


machine_context::machine_context(const std::shared_ptr<member_allocator>& _allocator, const std::shared_ptr<memory::executable_allocator>& _executable_allocator) : _allocator(_allocator), _executable_allocator(_executable_allocator), _string_manager(this->_allocator.get()), _variable_index(this->_allocator), _stack(this->_allocator.get(), 1024), _module_loader(allocator())
{
	if (!this->_allocator || !this->_executable_allocator) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
}

machine_context::machine_context(std::shared_ptr<member_allocator>&& _allocator, std::shared_ptr<memory::executable_allocator>&& _executable_allocator) : _allocator(std::move(_allocator)), _executable_allocator(std::move(_executable_allocator)), _string_manager(this->_allocator.get()), _variable_index(this->_allocator), _stack(this->_allocator.get(), 1024), _module_loader(allocator())
{
	if (!this->_allocator || !this->_executable_allocator) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
}

void machine_context::activate_context() noexcept
{
	_active_context = this;
	_active_allocator = allocator();
}

machine_context * machine_context::active_context() noexcept
{
	return _active_context;
}

machine_context::member_allocator * machine_context::active_allocator() noexcept
{
	return _active_allocator;
}

machine_context::member_allocator * machine_context::allocator() noexcept
{
	return _allocator.get();
}

memory::executable_allocator * machine_context::executable_allocator() noexcept
{
	return _executable_allocator.get();
}

string_manager & machine_context::string_manager() noexcept
{
	return _string_manager;
}

void BIA_MEMBER_CALLING_CONVENTION machine_context::destroy_from_stack(uint32_t _member_count)
{
	_stack.pop(_member_count);
}

void BIA_MEMBER_CALLING_CONVENTION machine_context::create_on_stack(framework::member ** _destination, uint32_t _member_count)
{
	_stack.push(_destination, _member_count);
}

void BIA_MEMBER_CALLING_CONVENTION machine_context::import_module(const char * _name)
{
	printf("import: %s\n", _name);

	// Search module in local directory

	// Search module in working directory
	if (auto _module = _module_loader.load_bll(std::string("./").append(_name).append(".bll").c_str(), _name)) {
		_module->load_all(this, address_of_member(_name));
		_module_loader.unload_module(_module);

		return;
	}

	// Search module in defined library directories


	// Search module in default lib directory

	throw exception::symbol_error(BIA_EM_MODULE_NOT_FOUND);
}

const char * machine_context::name_address(utility::string_key _name)
{
	return _string_manager.name_address(_name.string(), _name.length());
}

framework::member * machine_context::address_of_member(const char * _name)
{
	if (auto _result = _variable_index.find(_name)) {
		return _result;
	}

	// Create
	auto _allocation = _allocator->construct_block<framework::member, framework::undefined_member>();
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
	grammar::syntax::interpreter().interpret(_script, _compiler, *this);

	_compiler.finalize();

	return _compiler.code();
}


}
}
