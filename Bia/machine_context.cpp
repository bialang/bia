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

framework::member * const machine_context::none = reinterpret_cast<framework::member*>(intptr_t(-1));
thread_local machine_context * machine_context::_active_context = nullptr;
thread_local memory::allocator * machine_context::_active_allocator = nullptr;
thread_local memory::member_allocator * machine_context::_active_member_allocator = nullptr;
thread_local memory::big_int_allocator * machine_context::_active_big_int_allocator = nullptr;
thread_local utility::buffer_builder * machine_context::_active_buffer_builder = nullptr;


machine_context::machine_context(const std::shared_ptr<memory::allocator> & _allocator, const std::shared_ptr<memory::member_allocator> & _member_allocator, const std::shared_ptr<memory::big_int_allocator> & _big_int_allocator, const std::shared_ptr<memory::executable_allocator>& _executable_allocator) : _allocator(_allocator), _member_allocator(_member_allocator), _big_int_allocator(_big_int_allocator), _executable_allocator(_executable_allocator), _buffer_builder(_allocator.get()), _string_manager(this->_allocator.get()), _variable_index(this->_allocator), _stack(this->_allocator.get(), 1024), _module_loader(allocator())
{
	if (!this->_allocator || !this->_executable_allocator) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
}

machine_context::~machine_context()
{
	// For all member that are going to be destroyed
	activate_context();
}

void machine_context::activate_context() noexcept
{
	_active_context = this;
	_active_allocator = allocator();
	_active_member_allocator = member_allocator();
	_active_big_int_allocator = big_int_allocator();
	_active_buffer_builder = &buffer_builder();
}

void machine_context::unset_active_context() noexcept
{
	_active_context = nullptr;
	_active_allocator = nullptr;
	_active_member_allocator = nullptr;
	_active_big_int_allocator = nullptr;
	_active_buffer_builder = nullptr;
}

void machine_context::execute(stream::input_stream & _script)
{
	activate_context();

	compile_script(_script).execute();
}

void machine_context::add_script(const char * _name, stream::input_stream & _script)
{
	activate_context();

	_script_map.set(_name, compile_script(_script));
}

const machine_code & machine_context::get_script(const char * _name) const
{
	return _script_map.get(_name);
}

framework::member * machine_context::get_member(const char * _name, framework::member * _default)
{
	_name = _string_manager.name_address_or_null(_name, std::char_traits<char>::length(_name));

	if (auto _result = _variable_index.find(_name)) {
		return _result;
	} else if (_default == none) {
		throw exception::symbol_error(BIA_EM_UNKNOWN_MEMBER);
	}

	return _default;
}

const framework::member * machine_context::get_member(const char * _name, framework::member * _default) const
{
	_name = _string_manager.name_address_or_null(_name, std::char_traits<char>::length(_name));

	if (auto _result = _variable_index.find(_name)) {
		return _result;
	} else if (_default == none) {
		throw exception::symbol_error(BIA_EM_UNKNOWN_MEMBER);
	}

	return _default;
}

machine_context * machine_context::active_context() noexcept
{
	return _active_context;
}

memory::allocator * machine_context::active_allocator() noexcept
{
	return _active_allocator;
}

memory::member_allocator * machine_context::active_member_allocator() noexcept
{
	return _active_member_allocator;
}

memory::big_int_allocator * machine_context::active_big_int_allocator() noexcept
{
	return _active_big_int_allocator;
}

utility::buffer_builder * machine_context::active_buffer_builder() noexcept
{
	return _active_buffer_builder;
}

memory::allocator * machine_context::allocator() noexcept
{
	return _allocator.get();
}

memory::member_allocator * machine_context::member_allocator() noexcept
{
	return _member_allocator.get();
}

memory::big_int_allocator * machine_context::big_int_allocator() noexcept
{
	return _big_int_allocator.get();
}

memory::executable_allocator * machine_context::executable_allocator() noexcept
{
	return _executable_allocator.get();
}

utility::buffer_builder & machine_context::buffer_builder() noexcept
{
	return _buffer_builder;
}

string_manager & machine_context::string_manager() noexcept
{
	return _string_manager;
}

void BIA_MEMBER_CALLING_CONVENTION machine_context::destroy_from_stack(uint32_t _member_count)
{
	_stack.pop(_member_count);
}

void BIA_MEMBER_CALLING_CONVENTION machine_context::recreate_on_stack(uint32_t _member_count)
{
	_stack.recreate(_member_count);
}

void BIA_MEMBER_CALLING_CONVENTION machine_context::recreate_range_on_stack(framework::member * _begin, uint32_t _member_count)
{
	_stack.recreate_range(_begin, _member_count);
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
	auto _allocation = _member_allocator->template construct_member<framework::undefined_member>();
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

	return machine_code(std::make_pair(_output.buffer(), _output.size()), machine_schein(_allocator.get(), _executable_allocator.get()));
}


}
}
