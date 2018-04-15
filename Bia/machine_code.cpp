#include "machine_code.hpp"

#include <cstring>


namespace bia
{
namespace machine
{

machine_code::machine_code(std::pair<const uint8_t*, size_t> _machine_code, machine_schein _machine_schein) : _machine_schein(std::move(_machine_schein))
{
	// Allocate
	_entry_point = this->_machine_schein.get_allocator()->allocate(_machine_code.second, allocator::MEMORY_TYPE::EXECUTABLE_MEMORY);

	// Copy code
	if (_entry_point.address) {
		memcpy(_entry_point.address, _machine_code.first, _machine_code.second);
		this->_machine_schein.get_allocator()->change_protection(_entry_point, allocator::P_EXECUTE);
	}
}

machine_code::machine_code(machine_code && _rvalue) : _machine_schein(std::move(_rvalue._machine_schein))
{
	_entry_point = _rvalue._entry_point;
	_rvalue._entry_point = {};
}

machine_code::~machine_code()
{
	clear();
}

void machine_code::execute() const
{
	if (is_executable()) {
		try {
			reinterpret_cast<entry_point>(_entry_point.address)();
		} catch (...) {
			// Clean up

			throw;
		}
	}
}

void machine_code::clear()
{
	if (_entry_point.address) {
		_machine_schein.get_allocator()->deallocate(_entry_point, allocator::MEMORY_TYPE::EXECUTABLE_MEMORY);
	}
}

bool machine_code::is_executable() const noexcept
{
	return _entry_point.address && _entry_point.size;
}

machine_code & machine_code::operator=(machine_code && _rvalue)
{
	clear();

	// Move
	_machine_schein = std::move(_rvalue._machine_schein);
	_entry_point = _rvalue._entry_point;
	_rvalue._entry_point = {};

	return *this;
}

}
}