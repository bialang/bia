#include "schein.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace machine
{

schein::schein(machine::machine_context & _context) : _stack(_context.allocator(), 64/*TODO*/)
{
	this->_context = &_context;
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
	register_allocation(memory::cast_allocation<void>(_allocation), [_allocator = _context->big_int_allocator()](memory::universal_allocation _allocation) {
		_allocator->destroy_big_int(memory::cast_allocation<dependency::big_int>(_allocation));
	});
}

void schein::clear()
{
	auto _allocator = _context->allocator();

	for (auto & _allocation : _allocations) {
		if (_allocation.second) {
			_allocation.second(_allocation.first);
		} else {
			_allocator->deallocate(_allocation.first);
		}
	}

	_allocations.clear();
}

machine::machine_context * schein::machine_context() noexcept
{
	return _context;
}

machine::stack & schein::stack() noexcept
{
	return _stack;
}

}
}