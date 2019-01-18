#include "virtual_member_map.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

member_index_t virtual_member_map::get_or_insert(grammar::report::member_t _name)
{
	auto _result = _member_index.find(_name);

	if (_result != _member_index.end()) {
		return _result->second;
	}

	auto _tmp = _member_index.size();

	_member_index.insert({ _name, _tmp });

	return _tmp;
}

virtual_member_map::member_list_t virtual_member_map::to_member_list(machine_context & _context) const
{
	std::vector<framework::member*> _list;

	_list.resize(_member_index.size());

	for (auto & _index : _member_index) {
		_list[_index.second] = _context.address_of_member(_index.first);
	}

	return _list;
}

}
}
}