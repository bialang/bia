#ifndef BIA_RESOURCE_VIEW_HPP_
#define BIA_RESOURCE_VIEW_HPP_

#include "info.hpp"

#include <bia/memory/iterator.hpp>

namespace bia {
namespace resource {

struct View
{
	enum type type;
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
		if (type < type::string) {
			return -1;
		} else if (type > type::string) {
			return 1;
		}

		const auto ls = size();
		if (ls < length) {
			return -1;
		} else if (ls > length) {
			return 1;
		}

		for (auto i = first; i != last; ++i, ++string) {
			if (static_cast<char>(*i) < *string) {
				return -1;
			} else if (static_cast<char>(*i) < *string) {
				return 1;
			}
		}
		return 0;
	}
	int compare(const View& other) const noexcept
	{
		if (type < other.type) {
			return -1;
		} else if (type > other.type) {
			return 1;
		}

		const auto ls = size();
		const auto rs = other.size();
		if (ls < rs) {
			return -1;
		} else if (ls > rs) {
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
	bool operator<(const View& other) const noexcept
	{
		return compare(other) < 0;
	}
};

} // namespace resource
} // namespace bia

#endif
