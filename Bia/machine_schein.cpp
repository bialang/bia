#include "machine_schein.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

machine_schein & machine_schein::operator=(machine_schein && _move)
{
	clear();

	_allocator = _move._allocator;
	_executable_allocator = _move._executable_allocator;
	_big_int_allocator = _move._big_int_allocator;
	_allocations = std::move(_move._allocations);

	return *this;
}

}
}
}