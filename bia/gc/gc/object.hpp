#pragma once

#include "object_info.hpp"
#include "object_ptr.hpp"

#include <cstdint>
#include <util/gsl.hpp>
#include <utility>

namespace bia {
namespace gc {

/*
 This object must be implemented of all gc node object. Node objects are objects that must be destructed before
 deallocation and can contain references to other gc objects.
*/
class alignas(object_alignment) object
{
public:
	/*
	 Destructor.
	*/
	virtual ~object() = default;

protected:
	/*
	 Marks all children that were allocated by the gc. This functions should only mark its children and nothing more.

	 @param mark is required by gc_mark()
	*/
	virtual void gc_mark_children(bool mark) const noexcept = 0;
	/*
	 Marks the given pointer. If this pointer was not allocated by a gc the behavior is undefined.

	 @param ptr that should be marked
	 @param mark is the current mark
	*/
	static void gc_mark(util::not_null<const object*> ptr, bool mark) noexcept
	{
		auto info = _object_info(ptr);

		if (info->leaf) {
			info->mark.store(mark, std::memory_order_relaxed);
		} else {
			// newly marked -> mark children
			if (info->mark.exchange(mark, std::memory_order_relaxed) != mark) {
				static_cast<const object*>(ptr)->gc_mark_children(mark);
			}
		}
	}

private:
	friend class gc;

	static void _inject_object_info(util::not_null<void*> ptr, object_info&& info) noexcept
	{
		new (static_cast<std::int8_t*>(ptr) - sizeof(object_info)) object_info(std::move(info));
	}
	static util::not_null<object_info*> _object_info(util::not_null<const void*> ptr) noexcept
	{
		return const_cast<object_info*>(
		    reinterpret_cast<const object_info*>(static_cast<const std::int8_t*>(ptr) - sizeof(object_info)));
	}
};

} // namespace gc
} // namespace bia