#include <gc/gc.hpp>

namespace bia {
namespace gc {

thread_local gc* gc::active_gc_instance = nullptr;

gc* gc::active_gc() noexcept
{
	return active_gc_instance;
}

} // namespace gc
} // namespace bia