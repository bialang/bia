#include "system.hpp"

using namespace bia::compiler::type;

system::system()
{}

system::~system()
{}

definition* system::get(const resource::view& name)
{
	const auto it = _definitions.find(name);
	if (it == _definitions.end()) {
		return nullptr;
	}
	return it->second;
}
