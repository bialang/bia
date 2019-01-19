#include "schein.hpp"


namespace bia
{
namespace machine
{

schein::schein(memory::allocator * _allocator, memory::executable_allocator * _executable_allocator, memory::big_int_allocator * _big_int_allocator) : _allocator(_allocator), _executable_allocator(_executable_allocator), _big_int_allocator(_big_int_allocator)
{
}

schein::~schein()
{
	clear();
}

void schein::register_allocation(memory::universal_allocation _allocation, deleter_function_t && _deleter)
{
	_allocations.emplace_back(std::make_pair(_allocation, std::move(_deleter)));
}

void schein::register_allocation(memory::universal_allocation _allocation, const deleter_function_t & _deleter)
{
	_allocations.emplace_back(std::make_pair(_allocation, _deleter));
}

void schein::register_big_int(memory::big_int_allocation _allocation)
{
	register_allocation(memory::cast_allocation<void>(_allocation), [this](memory::universal_allocation _allocation) {
		_big_int_allocator->destroy_big_int(memory::cast_allocation<dependency::big_int>(_allocation));
	});
}

void schein::clear()
{
	for (auto & _allocation : _allocations) {
		if (_allocation.second) {
			_allocation.second(_allocation.first);
		} else {
			_allocator->deallocate(_allocation.first);
		}
	}

	_allocations.clear();
}

memory::allocator * schein::allocator() noexcept
{
	return _allocator;
}

memory::executable_allocator * schein::executable_allocator() noexcept
{
	return _executable_allocator;
}

}
}