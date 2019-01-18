#include "script_map.hpp"
#include "exception.hpp"



namespace bia
{
namespace machine
{

script_map::script_map() noexcept
{
}

script_map::script_map(script_map && _move)
{
	_scripts.swap(_move._scripts);
}

void script_map::set(const char * _name, platform::machine_code && _code)
{
	_scripts.emplace(std::make_pair(_name, std::move(_code)));
}

const platform::machine_code & script_map::get(const char * _name) const
{
	auto _result = _scripts.find(_name);

	if (_result == _scripts.end()) {
		throw exception::symbol_error(BIA_EM_UNKNOWN_SCRIPT);
	}

	return _result->second;
}

}
}