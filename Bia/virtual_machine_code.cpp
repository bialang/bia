#include "virtual_machine_code.hpp"

#include <cstring>


namespace bia
{
namespace machine
{
namespace virtual_machine
{

virtual_machine_code::virtual_machine_code(memory::universal_allocation _code, virtual_machine_schein && _schein, bool _take_ownership) : _schein(std::move(_schein))
{
	// Copy buffer
	if (!_take_ownership) {
		auto _tmp = this->_schein.allocator()->allocate(_code.second);

		std::memcpy(_tmp.first, _code.first, _code.second);

		_code = _tmp;
	}

	this->_code = memory::cast_allocation<uint8_t>(_code);
}

virtual_machine_code::virtual_machine_code(virtual_machine_code && _move) : _schein(std::move(_move._schein))
{
	_code = std::move(_move._code);

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
		_schein.allocator()->deallocate(memory::cast_allocation<void>(_code));
		_code.clear();
	}
}

bool virtual_machine_code::is_executable() const noexcept
{
	return _code;
}

}
}
}