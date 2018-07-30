#include "variable_index.hpp"


namespace bia
{
namespace machine
{

variable_index::variable_index(const std::shared_ptr<memory::allocator> & _allocator) noexcept : _map(allocator_type(_allocator))
{
}

framework::member * variable_index::add(const char * _key, value_type _value)
{
	auto _result = _map.emplace(_key, utility::make_guard(std::move(_value), &guard_action));

	if (!_result.second) {
		throw;
	}

	return _result.first->second.get().first;
}

framework::member * variable_index::find(const char * _key)
{
	auto _result = _map.find(_key);

	return _result == _map.end() ? nullptr : _result->second.get().first;
}

void variable_index::guard_action(value_type & _value)
{
	printf("guard_action: destroying %p with %zi bytes\n", _value.first, _value.second);
}

}
}