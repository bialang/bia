#include "virtual_machine_code.hpp"
#include "op_code.hpp"
#include "create_member.hpp"

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
	size_t _cursor = 0;
	auto & _globals = _schein.globals();
	auto & _stack = _schein.stack();

	switch (_code.first[_cursor++]) {
	case OC_RETURN:
		break;
	case OC_PARAM_0:
		_stack.push(stack::element_t(0));

		break;
	case OC_INSTANTIATE_0:
	{
		uint32_t _index = *reinterpret_cast<const uint32_t*>(_code.first + _cursor);

		_cursor += 4;

		framework::create_member(_globals[_index], 0);

		break;
	}
	default:
		BIA_IMPLEMENTATION_ERROR;
	}
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