#include <gc/memory_allocator.hpp>
#include <gc/simple_allocator.hpp>
#include <memory>

namespace bia {
namespace gc {

std::unique_ptr<memory_allocator> mem_allocator(new simple_allocator());

void memory_allocator::default_allocator(memory_allocator* allocator) noexcept
{
	mem_allocator.reset(allocator);
}

memory_allocator* memory_allocator::default_allocator() noexcept
{
	return mem_allocator.get();
}

} // namespace gc
} // namespace bia