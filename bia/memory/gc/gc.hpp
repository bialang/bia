#ifndef BIA_MEMORY_GC_GC_HPP_
#define BIA_MEMORY_GC_GC_HPP_

#include "../allocator.hpp"
#include "../stack.hpp"

#include <cstddef>
#include <memory>
#include <mutex>
#include <vector>

namespace bia {
namespace memory {
namespace gc {

class GC
{
public:
	GC(util::Not_null<std::shared_ptr<Allocator>> allocator);
	/// Allocates GC monitored memory.
	void* allocate(std::size_t size);
	void run();
	void register_stack(Stack& stack);
	util::Not_null<std::shared_ptr<Allocator>> allocator() noexcept;

private:
	std::shared_ptr<Allocator> _allocator;
	std::mutex _mutex;
	/// All allocated pointers that are GC monitored.
	std::vector<void*> _pointers;
	std::vector<Stack*> _roots;
};

} // namespace gc
} // namespace memory
} // namespace bia

#endif
