#include "machine_schein.hpp"

namespace bia
{
namespace machine
{

machine_schein::machine_schein(memory::allocator * _allocator, memory::executable_allocator * _executable_allocator) noexcept
{
	this->_allocator = _allocator;
	this->_executable_allocator = _executable_allocator;
}

machine_schein::~machine_schein()
{
	delete_all_allocations();
}

void machine_schein::register_allocation(memory::universal_allocation _allocation, deleter_function_signature _deleter)
{
	_allocated.push_back({ _allocation, _deleter });
}

void machine_schein::delete_all_allocations()
{
	for (auto i = _allocated.end(); i != _allocated.begin();) {
		auto _allocation = *i;

		i = _allocated.erase(i);

		if (i->second) {
			i->second(i->first);
		}

		_allocator->deallocate(i->first);
	}
}

memory::allocator * machine_schein::allocator() noexcept
{
	return _allocator;
}

memory::executable_allocator * machine_schein::executable_allocator() noexcept
{
	return _executable_allocator;
}

machine_schein & machine_schein::operator=(machine_schein && _move)
{
	delete_all_allocations();

	_allocator = _move._allocator;
	_executable_allocator = _move._executable_allocator;
	_allocated = std::move(_move._allocated);

	return *this;
}

}
}