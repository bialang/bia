#include "manager.hpp"

#include <bia/error/exception.hpp>

using namespace bia::compiler::symbol;

manager::manager()
{
	_scopes.emplace_back();
}

void manager::open_scope()
{
	_scopes.emplace_back();
}

void manager::close_scope()
{
	BIA_EXPECTS(_scopes.size() > 1);
	for (const auto& it : _scopes.back()) {
		_variables.erase(it);
	}
	_scopes.pop_back();
}

builder manager::declare(const resource::view& name)
{
	if (_variables.find(name) != _variables.end() || _declared.find(name) != _declared.end()) {
		BIA_THROW(error::code::variable_alread_declared);
	}
	_declared.insert({ name, bytecode::member::local{ _index } });
	return { this, name, bytecode::member::local{ _index++ } };
}

void manager::_accept_declared(const resource::view& name, variable var)
{
	_declared.erase(name);
	_variables.insert({ name, std::move(var) });
}

void manager::_decline_declared(const resource::view& name)
{
	_declared.erase(name);
}
