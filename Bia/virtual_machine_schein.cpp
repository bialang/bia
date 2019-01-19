#include "virtual_machine_schein.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

virtual_machine_schein::virtual_machine_schein(machine_context & _context) : schein(_context.allocator(), _context.executable_allocator(), _context.big_int_allocator())
{
	this->_context = &_context;
}

void virtual_machine_schein::set_member_map(const virtual_member_map & _member_map)
{
	_globals = _member_map.to_member_list(*_context);
}

const virtual_member_map::member_list_t & virtual_machine_schein::globals() const noexcept
{
	return _globals;
}

}
}
}