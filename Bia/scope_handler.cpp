#include "scope_handler.hpp"
#include "exception.hpp"

#include <algorithm>

namespace bia
{
namespace compiler
{

scope_handler::scope_handler(machine::virtual_machine::virtual_translator & _translator, scope_handler * _parent) : _translator(_translator)
{
	this->_parent = _parent;
	_max_needed = 0;

	if (_parent) {
		open_scope();
	}
}

void scope_handler::open_scope()
{
	// First local scope
	if (!has_open_scopes()) {
		if (!_variables.empty()) {
			BIA_IMPLEMENTATION_ERROR;
		}

		_counter = temp_counter();

		_variables_in_scopes.push_back(0);
	} else {
		_translator.open_scope();
		_variables_in_scopes.push_back(_counter.peek());
	}
}

void scope_handler::close_scope()
{
	// No scope open
	if (!has_open_scopes()) {
		BIA_IMPLEMENTATION_ERROR;
	}

	variable_index_t _count = 0;
	auto _current_scope = _variables_in_scopes.size();

	// Remove variables from map
	for (auto i = _variables.begin(); i != _variables.end();) {
		if (i->second.second == _current_scope) {
			i = _variables.erase(i);

			++_count;
		} else {
			++i;
		}
	}

	// Scope cleanup
	_max_needed = std::max(_max_needed, _counter.current());

	_counter.pop(_variables_in_scopes.back());
	_variables_in_scopes.pop_back();
	_translator.close_scope(_count);
}

void scope_handler::finalize()
{
	if (_parent) {
		close_scope();
	}
}

bool scope_handler::has_open_scopes() const noexcept
{
	return !_variables_in_scopes.empty();
}

scope_handler::variable_index_t scope_handler::declare(const char * _name)
{
	if (!has_open_scopes()) {
		BIA_IMPLEMENTATION_ERROR;
	} 
	
	auto _result = _variables.find(_name);

	// Not declared
	if (_result == _variables.end()) {
		_variables.emplace(std::make_pair(_name, std::make_pair(_counter.next(), _variables_in_scopes.size())));

		return _counter.current();
	}

	return _result->second.first;
}

scope_handler::variable_index_t scope_handler::variable_index(const char * _name)
{
	auto _result = _variables.find(_name);

	return _result == _variables.end() ? not_found : _result->second.first;
}

scope_handler::variable_index_t scope_handler::max_needed() const noexcept
{
	return _max_needed;
}

}
}