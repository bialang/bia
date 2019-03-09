#include "string_manager.hpp"
#include "share.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace machine
{

string_manager::~string_manager()
{
}

string_manager::index_t string_manager::register_string(memory::universal_allocation _string)
{
	_strings.emplace_back();
	_strings.back()->create<dstring_resource>(_string, machine_context::active_allocator());

	return _strings.size() - 1;
}

}
}