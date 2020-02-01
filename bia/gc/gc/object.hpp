#pragma once

#include "object_info.hpp"
#include "object_ptr.hpp"

#include <cstdint>
#include <log/log.hpp>
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
	/**
	 * Destructor.
	 */
	virtual ~object() = default;
	/**
	 * Marks the given pointer for the gc cycle. If `ptr` was not allocated by a gc, the behavior is undefined.
	 *
	 * @warning this function should only be called inside of gc_mark_childred()
	 *
	 * @param ptr the pointer to mark
	 * @param mark the mark provided by the gc
	 */
	static void gc_mark(util::not_null<const void*> ptr, bool mark) noexcept
	{
		auto info = _object_info(ptr);

		BIA_LOG(TRACE, "trying to mark info={}", static_cast<void*>(info));

		if (info->leaf) {
			info->mark = mark;
		} else {
			// newly marked -> mark children
			if (info->mark != mark) {
				info->mark = mark;

				BIA_LOG(TRACE, "marking children of info={}", static_cast<void*>(info));

				static_cast<const object*>(ptr.get())->gc_mark_children(mark);
			}
		}
	}

protected:
	/*
	 Marks all children that were allocated by the gc. This functions should only mark its children and nothing more.

	 @param mark is required by gc_mark()
	*/
	virtual void gc_mark_children(bool mark) const noexcept = 0;

private:
	static util::not_null<object_info*> _object_info(util::not_null<const void*> ptr) noexcept
	{
		return const_cast<object_info*>(static_cast<const object_info*>(ptr.get()) - 1);
	}
};

} // namespace gc
} // namespace bia