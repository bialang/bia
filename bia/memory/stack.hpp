#ifndef BIA_MEMORY_STACK_HPP_
#define BIA_MEMORY_STACK_HPP_

#include "allocator.hpp"

#include <bia/error/exception.hpp>
#include <bia/log/log.hpp>
#include <bia/util/gsl.hpp>
#include <cstdint>
#include <cstring>
#include <memory>
#include <mutex>
#include <type_traits>

namespace bia {
namespace memory {
namespace gc {

class GC;

}

template<bool>
class Frame;

class Stack
{
public:
	Stack(util::Not_null<std::shared_ptr<Allocator>> allocator, std::size_t size)
	    : _allocator{ std::move(allocator.get()) }
	{
		_memory = { static_cast<util::Byte*>(_allocator->allocate(size)), size };
		_meta   = { static_cast<std::uint32_t*>(
                _allocator->allocate(size / sizeof(void*) / 8 * sizeof(std::uint32_t))),
              size / sizeof(void*) / 8 };
		std::memset(_memory.begin(), 0, _memory.size_bytes());
		std::memset(_meta.begin(), 0, _meta.size_bytes());
	}
	Stack(const Stack& copy) = delete;
	~Stack() noexcept
	{
		// BIA_LOG(TRACE, "destroying stack");
		_allocator->deallocate(_memory.data());
		_allocator->deallocate(_meta.data());
	}
	Stack& operator=(const Stack& copy) = delete;

private:
	friend gc::GC;
	template<bool>
	friend class Frame;
	mutable std::mutex _mutex;
	std::shared_ptr<Allocator> _allocator;
	/// The actual stack data.
	util::Span<util::Byte*> _memory;
	/// Meta information for the GC.
	util::Span<std::uint32_t*> _meta;
};

} // namespace memory
} // namespace bia

#endif
