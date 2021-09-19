#ifndef BIA_MEMORY_GC_GC_HPP_
#define BIA_MEMORY_GC_GC_HPP_

#include "../allocator.hpp"
#include "../stack.hpp"
#include "types.hpp"

#include <bia/util/algorithm.hpp>
#include <bia/util/gsl.hpp>
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
	GC(const GC& copy) = delete;
	~GC() noexcept;
	/// Allocates GC monitored memory.
	GC_able<void*> allocate(std::size_t size);
	template<typename Type, typename... Arguments>
	typename std::enable_if<std::is_base_of<Base, Type>::value, GC_able<Type*>>::type
	  create(Arguments&&... arguments)
	{
		static_assert(alignof(Type) <= alignof(std::max_align_t),
		              "Alignments greater than the one of std::max_align_t are not supported");

		const auto ptr = static_cast<Type*>(_allocator->checked_allocate(sizeof(Type)).get());
		BIA_ASSERT(util::is_aligned(ptr, alignof(Type)));
		BIA_LOG(TRACE, "GC created ptr={}", static_cast<void*>(ptr));

		// create object
		try {
			new (ptr) Type{ std::forward<Arguments>(arguments)... };
		} catch (...) {
			_allocator->deallocate(ptr);
			throw;
		}
		const auto observable = reinterpret_cast<Type*>(reinterpret_cast<std::intptr_t>(ptr) | 0x1);

		try {
			std::lock_guard<std::mutex> _{ _mutex };
			_pointers.push_back(observable);
		} catch (...) {
			BIA_LOG(CRITICAL, "Failed to append newly create GC able object to the pointers list.");
			ptr->~Type();
			_allocator->deallocate(ptr);
			throw;
		}
		return { observable };
	}
	void run();
	void register_stack(Stack& stack);
	void unregister_stack(Stack& stack);
	util::Not_null<std::shared_ptr<Allocator>> allocator() noexcept;
	GC& operator=(const GC& copy) = delete;

private:
	std::shared_ptr<Allocator> _allocator;
	std::mutex _mutex;
	/// All allocated pointers that are GC monitored.
	std::vector<void*> _pointers;
	/// All reachable pointers are some kind of a child of these pointers.
	std::vector<Stack*> _roots;

	void _sweep(util::Not_null<GC_able<void*>> ptr);
};

} // namespace gc
} // namespace memory
} // namespace bia

#endif
