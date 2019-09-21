#pragma once

#include "object_info.hpp"
#include "object_ptr.hpp"

namespace bia {
namespace gc {

/*
 This object must be implemented of all gc node object. Node objects are objects that must be destructed before deallocation and can contain references to other gc objects.
*/
class object
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
	static void gc_mark(void* ptr, bool mark)
	{
		auto info = object_info(ptr);

		if (info->leaf) {
			info->marked.store(mark, std::memory_order_relaxed);
		} else {
			if (info->marked.exchange(mark, std::memory_order_relaxed) !=
				mark) {
				static_cast<object*>(ptr)->gc_mark_children(mark);
			}
		}
	}

private:
	friend class gc;

	static void* inject_object_info(void* ptr)
	{}
	static object_info* object_info(void* ptr)
	{}
};

} // namespace gc
} // namespace bia