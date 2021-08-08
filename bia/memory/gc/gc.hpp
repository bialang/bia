#ifndef BIA_MEMORY_GC_GC_HPP_
#define BIA_MEMORY_GC_GC_HPP_

#include "../allocator.hpp"
#include "../stack.hpp"
#include "types.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <type_traits>
#include <utility>
#include <vector>

namespace bia {
namespace memory {
namespace gc {

class GC
{
public:
	GC(util::Not_null<std::shared_ptr<Allocator>> allocator);
	/// Allocates GC monitored memory.
	GC_able<void*> allocate(std::size_t size);
	template<typename Type, typename... Arguments>
	typename std::enable_if<std::is_base_of<Base, Type>::value, GC_able<Type*>>::type
	  create(Arguments&&... arguments)
	{
		// TODO check alignment
		auto ptr = static_cast<Type*>(_allocator->allocate(sizeof(Type)));
		BIA_LOG(TRACE, "GC created ptr={}", static_cast<void*>(ptr));
		// TODO handle exception
		new (ptr) Type{ std::forward<Arguments>(arguments)... };
		ptr = reinterpret_cast<Type*>(reinterpret_cast<std::intptr_t>(ptr) | 0x1);
		std::lock_guard<std::mutex> _{ _mutex };
		_pointers.push_back(ptr);
		return { ptr };
	}
	void run();
	void register_stack(Stack& stack);
	void unregister_stack(Stack& stack);
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
