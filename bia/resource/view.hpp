#ifndef BIA_RESOURCE_VIEW_HPP_
#define BIA_RESOURCE_VIEW_HPP_

#include "info.hpp"

#include <bia/gc/memory/iterator.hpp>

namespace bia {
namespace resource {

struct view
{
	enum type type;
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
	int compare(const view& other) const noexcept
	{
		if (type < other.type) {
			return -1;
		} else if (type > other.type) {
			return 1;
		} else if (size < other.size) {
			return -1;
		} else if (size > other.size) {
			return 1;
		}

		for (auto i = first, j = other.first; i != last; ++i, ++j) {
			if (*i < *j) {
				return -1;
			} else if (*i > *j) {
				return 1;
			}
		}

		return 0;
	}
	bool operator<(const view& other) const noexcept
	{
		return compare(other) < 0;
	}
};

} // namespace resource
} // namespace bia

#endif
