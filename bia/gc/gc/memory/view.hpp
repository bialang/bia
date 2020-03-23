#ifndef BIA_GC_MEMORY_VIEW_HPP_
#define BIA_GC_MEMORY_VIEW_HPP_

#include "iterator.hpp"

namespace bia {
namespace gc {
namespace memory {

class view
{
public:
	view(iterator begin, iterator end) noexcept : _begin(std::move(begin)), _end(std::move(end))
	{}
	iterator begin() const
	{
		return _begin;
	}
	iterator end() const
	{
		return _end;
	}

private:
	iterator _begin;
	iterator _end;
};

} // namespace memory
} // namespace gc
} // namespace bia

#endif