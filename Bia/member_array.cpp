#include "member_array.hpp"
#include "undefined_member.hpp"


namespace bia
{
namespace machine
{

member_array::member_array(memory::member_allocator * _allocator)
{
	this->_allocator = _allocator;
}

member_array::~member_array()
{
	for (auto i = _members.data(), _cond = i + _members.size(); i < _cond; ++i) {
		_allocator->destroy_member(*i);
	}
}

void member_array::create(index_t _size)
{
	if (_members.size() < _size) {
		if (!_members.empty()) {
			BIA_IMPLEMENTATION_ERROR;
		}

		_members.resize(_size);

		for (auto i = _members.data(), _cond = i + _members.size(); i < _cond; ++i) {
			*i = _allocator->construct_member<framework::undefined_member>();
		}

		_ends.first = _members.front();
		_ends.second = _members.back();
	}
}

framework::member * member_array::from_front(index_t _index)
{
	return _ends.first + _index;
}

framework::member * member_array::from_back(index_t _index)
{
	return _ends.second - _index;
}

}
}