#pragma once

#include <cstdint>
#include <vector>

#include "member.hpp"
#include "member_allocator.hpp"


namespace bia
{
namespace machine
{

class member_array
{
public:
	typedef uint32_t index_t;

	member_array(memory::member_allocator * _allocator);
	~member_array();
	void create(index_t _size);
	framework::member * from_front(index_t _index);
	framework::member * from_back(index_t _index);

private:
	memory::member_allocator * _allocator;
	std::vector<memory::member_allocator::member_allocation_t> _members;
	std::pair<framework::member*, framework::member*> _ends;
};

}
}