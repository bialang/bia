#include "variable_index.hpp"


namespace bia
{
namespace machine
{

variable_index::variable_index(const std::shared_ptr<memory::allocator> & _allocator) noexcept : _map(allocator_type(_allocator))
{
}

framework::member * variable_index::add(utility::string_key _key, memory::allocator::allocation<framework::member> _value)
{
	_map.emplace(std::move(_key), std::move(_value));

	return static_cast<framework::member*>(_value.first);
}

framework::member * variable_index::find(utility::string_key _key)
{
	auto _result = _map.find(_key);

	return _result == _map.end() ? nullptr : _result->second.get();
}

}
}