#include "builder.hpp"

#include "manager.hpp"

using namespace bia::compiler::symbol;

builder::builder(builder&& move) noexcept : _name{ move._name }
{
	*this = std::move(move);
}

builder::~builder()
{
	_drop();
}

void builder::build()
{
	if (!_manager) {
	} else if (!_definition) {
	}
	_manager->_accept_declared(_name, { _location, _definition });
	_manager = nullptr;
}

void builder::definition(type::definition* def) noexcept
{
	_definition = def;
}

bia::compiler::type::definition* builder::definition() const noexcept
{
	return _definition;
}

location_type builder::location() const noexcept
{
	return _location;
}

builder& builder::operator=(builder&& move) noexcept
{
	_drop();
	_manager      = move._manager;
	_definition   = move._definition;
	_location     = std::move(move._location);
	_name         = std::move(move._name);
	move._manager = nullptr;
	return *this;
}

builder::builder(manager* manager, resource::view name, location_type location)
    : _location{ location }, _name{ std::move(name) }
{
	_manager = manager;
}

void builder::_drop() noexcept
{
	if (_manager) {
		_manager->_decline_declared(_name);
	}
}
