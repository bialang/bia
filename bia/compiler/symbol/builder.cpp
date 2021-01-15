#include "builder.hpp"

#include "manager.hpp"

using namespace bia::compiler::symbol;

Builder::Builder(Builder&& move) noexcept : _name{ move._name }
{
	*this = std::move(move);
}

Builder::~Builder()
{
	_drop();
}

void Builder::build()
{
	if (!_manager) {
	} else if (!_definition) {
	}
	_manager->_accept_declared(_name, { _location, _definition });
	_manager = nullptr;
}

void Builder::definition(type::Definition* def) noexcept
{
	_definition = def;
}

bia::compiler::type::Definition* Builder::definition() const noexcept
{
	return _definition;
}

Location Builder::location() const noexcept
{
	return _location;
}

Builder& Builder::operator=(Builder&& move) noexcept
{
	_drop();
	_manager      = move._manager;
	_definition   = move._definition;
	_location     = std::move(move._location);
	_name         = std::move(move._name);
	move._manager = nullptr;
	return *this;
}

Builder::Builder(Manager* manager, resource::View name, Location location)
    : _location{ location }, _name{ std::move(name) }
{
	_manager = manager;
}

void Builder::_drop() noexcept
{
	if (_manager) {
		_manager->_decline_declared(_name);
	}
}
