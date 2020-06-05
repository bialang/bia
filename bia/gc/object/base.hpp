#ifndef BIA_GC_OBJECT_BASE_HPP_
#define BIA_GC_OBJECT_BASE_HPP_

#include "header.hpp"
#include "pointer.hpp"

#include <bia/log/log.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace gc {

class gc;

namespace object {

/**
 * This object must be implemented ny all gc node objects. Node objects are objects that must be destructed
 * before deallocation and can contain references to other gc objects.
 */
class alignas(alignment) base
{
public:
	/**
	 * Destructor.
	 */
	virtual ~base() = default;
	/**
	 * Marks all children that were allocated by the gc. This functions should only mark its children and
	 * nothing more.
	 *
	 * @param mark is required by gc_mark()
	 */
	virtual void gc_mark_children(bool mark) const noexcept = 0;

protected:
	friend gc;
	virtual void register_gcables(gc& gc) const noexcept = 0;
};

/**
 * Marks the given pointer for the gc cycle. If `ptr` was not allocated by a gc, the behavior is
 * undefined.
 *
 * @warning this function should only be called inside of gc_mark_childred()
 *
 * @param ptr the pointer to mark
 * @param mark the mark provided by the gc
 */
inline void gc_mark(util::not_null<const void*> ptr, bool mark) noexcept
{
	auto info = const_cast<header*>(static_cast<const header*>(ptr.get()) - 1);

	BIA_LOG(TRACE, "trying to mark info={}", static_cast<void*>(info));

	if (info->leaf) {
		info->mark = mark;
	} else {
		// newly marked -> mark children
		if (info->mark != mark) {
			info->mark = mark;

			BIA_LOG(TRACE, "marking children of info={}", static_cast<void*>(info));

			static_cast<const base*>(ptr.get())->gc_mark_children(mark);
		}
	}
}

} // namespace object
} // namespace gc
} // namespace bia

#endif
