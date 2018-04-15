#include "machine_schein.hpp"

namespace bia
{
namespace machine
{

machine_schein::machine_schein(allocator * _allocator)
{
	this->_allocator = _allocator;
}

machine_schein::~machine_schein()
{
	delete_all_allocations();
}

void machine_schein::register_allocation(allocator::universal_allocation _allocation)
{
	_allocated.push_back(_allocation);
}

void machine_schein::delete_all_allocations()
{
	for (auto & _allocation : _allocated) {
		_allocator->deallocate(_allocation, allocator::MEMORY_TYPE::NORMAL);
	}
}

allocator * machine_schein::get_allocator() noexcept
{
	return _allocator;
}

machine_schein & machine_schein::operator=(machine_schein && _rvalue)
{
	delete_all_allocations();

	_allocator = _rvalue._allocator;
	_allocated = std::move(_rvalue._allocated);

	return *this;
}

}
}