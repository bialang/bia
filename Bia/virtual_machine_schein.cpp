#include "virtual_machine_schein.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

void virtual_machine_schein::set_member_map(const utility::index_map & _member_map)
{
	_globals = _member_map.to_list<framework::member*>([&](auto _name) { return _context->address_of_member(_name); });
}

void virtual_machine_schein::set_name_map(const utility::index_map & _name_map)
{
	_names = _name_map.to_list<name_manager::name_t>([](auto _name) { return _name; });
}

const virtual_machine_schein::member_list_t & virtual_machine_schein::globals() const noexcept
{
	return _globals;
}

const virtual_machine_schein::name_list_t & virtual_machine_schein::names() const noexcept
{
	return _names;
}

}
}
}