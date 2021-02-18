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
	template<typename Type>
	void store(std::int32_t offset, const Type& value, bool mark = false)
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");

		std::lock_guard<std::mutex> _{ _mutex };
		const auto position = _memory.begin() + offset;
		if (reinterpret_cast<std::intptr_t>(position) % alignof(Type)) {
			BIA_THROW(error::Code::bad_stack_alignment);
		} else if (position < _memory.begin() || position + sizeof(Type) > _memory.end()) {
			BIA_THROW(error::Code::out_of_stack);
		}
		std::memcpy(position, &value, sizeof(value));
		if (mark) {
			_meta[offset / sizeof(void*) / 8] |= 1 << offset / sizeof(void*) % 8;
		} else {
			_meta[offset / sizeof(void*) / 8] &= ~(1 << offset / sizeof(void*) % 8);
		}
	}
	template<typename Type>
	Type load(std::int32_t offset) const
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");

		std::lock_guard<std::mutex> _{ _mutex };
		const auto position = _memory.begin() + offset;
		if (reinterpret_cast<std::intptr_t>(position) % alignof(Type)) {
			BIA_THROW(error::Code::bad_stack_alignment);
		} else if (position < _memory.begin() || position + sizeof(Type) > _memory.end()) {
			BIA_THROW(error::Code::out_of_stack);
		}
		Type value{};
		std::memcpy(&value, position, sizeof(value));
		return value;
	}
	Stack& operator=(const Stack& copy) = delete;

private:
	friend gc::GC;
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
