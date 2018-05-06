#include "machine_schein.hpp"

namespace bia
{
namespace machine
{

machine_schein::machine_schein(memory::allocator * _allocator, memory::executable_allocator * _executable_allocator)
{
	this->_allocator = _allocator;
	this->_executable_allocator = _executable_allocator;
}

machine_schein::~machine_schein()
{
	delete_all_allocations();
}

void machine_schein::register_allocation(memory::allocator::universal_allocation _allocation)
{
	_allocated.push_back(_allocation);
}

void machine_schein::delete_all_allocations()
{
	for (auto i = _allocated.end(); i != _allocated.begin();) {
		auto _allocation = *i;

		i = _allocated.erase(i);
		
		_allocator->deallocate(*i);
	}
}

memory::allocator * machine_schein::get_allocator() noexcept
{
	return _allocator;
}

memory::executable_allocator * machine_schein::get_executable_allocator() noexcept
{
	return _executable_allocator;
}

machine_schein & machine_schein::operator=(machine_schein && _rvalue)
{
	delete_all_allocations();

	_allocator = _rvalue._allocator;
	_executable_allocator = _rvalue._executable_allocator;
	_allocated = std::move(_rvalue._allocated);

	return *this;
}

}
}