#include "machine_context.hpp"


namespace bia
{
namespace machine
{

machine_context::machine_context(std::shared_ptr<memory::allocator> _allocator) noexcept : _allocator(std::move(_allocator))
{
}

memory::allocator * machine_context::get_allocator() noexcept
{
	return _allocator.get();
}


}
}