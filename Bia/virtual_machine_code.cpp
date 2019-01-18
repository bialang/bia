#include "virtual_machine_code.hpp"

#include <cstring>


namespace bia
{
namespace machine
{
namespace virtual_machine
{

virtual_machine_code::virtual_machine_code(memory::universal_allocation _code, machine_context & _context, const virtual_member_map & _member_map, bool _take_ownership) : _globals(_member_map.to_member_list(_context))
{
	_allocator = _context.allocator();

	// Copy buffer
	if (!_take_ownership) {
		auto _tmp = _allocator->allocate(_code.second);

		std::memcpy(_tmp.first, _code.first, _code.second);

		_code = _tmp;
	}

	this->_code = memory::cast_allocation<uint8_t>(_code);
}

virtual_machine_code::virtual_machine_code(virtual_machine_code && _move) : _globals(std::move(_move._globals))
{
	_code = std::move(_move._code);
	_allocator = _move._allocator;

	_move.clear();
}

virtual_machine_code::~virtual_machine_code()
{
	clear();
}

void virtual_machine_code::execute()
{
	BIA_NOT_IMPLEMENTED;
}

void virtual_machine_code::clear()
{
	if (_code) {
		_allocator->deallocate(memory::cast_allocation<void>(_code));
		_code.clear();
		_globals.clear();
	}
}

bool virtual_machine_code::is_executable() const noexcept
{
	return _code;
}

}
}
}