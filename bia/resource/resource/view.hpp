#ifndef BIA_RESOURCE_VIEW_HPP_
#define BIA_RESOURCE_VIEW_HPP_

#include "info.hpp"

#include <gc/memory/iterator.hpp>

namespace bia {
namespace resource {

struct view
{
	type type;
	std::size_t size;
	gc::memory::iterator first;
	gc::memory::iterator last;

	gc::memory::iterator begin() const noexcept
	{
		return first;
	}
	gc::memory::iterator end() const noexcept
	{
		return last;
	}
};

} // namespace resource
} // namespace bia

#endif