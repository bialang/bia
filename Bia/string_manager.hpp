#pragma once

#include <vector>

#include "allocator.hpp"
//#include "share.hpp"
#include "string_resource.hpp"


namespace bia
{
namespace machine
{

class string_manager
{
public:
	void register_string(memory::universal_allocation _string)
	{

	}
	template<typename Char_type>
	const Char_type * string(size_t _index)
	{
		return nullptr;
	}
private:
	//std::vector<utility::share<string_resource_t>> _strings;
};

}
}