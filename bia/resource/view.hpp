#ifndef BIA_RESOURCE_VIEW_HPP_
#define BIA_RESOURCE_VIEW_HPP_

#include "info.hpp"

#include <bia/memory/iterator.hpp>
#include <bia/util/algorithm.hpp>

namespace bia {
namespace resource {

struct View
{
	Type type;
	memory::iterator first;
	memory::iterator last;

	memory::iterator begin() const noexcept
	{
		return first;
	}
	memory::iterator end() const noexcept
	{
		return last;
	}
	std::size_t size() const noexcept
	{
		return last - first;
	}
	int compare(const char* string, std::size_t length) const noexcept
	{
		if (auto n = util::compare(type, Type::string)) {
			return n;
		}
		return util::compare_ranges(first, last, string, string + length, [](util::Byte left, char right) {
			return util::compare(left, static_cast<util::Byte>(right));
		});
	}
	int compare(const View& other) const noexcept
	{
		if (auto n = util::compare(type, other.type)) {
			return n;
		}
		return util::compare_ranges(first, last, other.first, other.last);
	}
	bool operator<(const View& other) const noexcept
	{
		return compare(other) < 0;
	}
};

} // namespace resource
} // namespace bia

#endif
