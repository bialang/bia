#include "view.hpp"

using namespace bia::memory;

view::view(iterator first, iterator last) noexcept : _first(std::move(first)), _last(std::move(last))
{}

iterator view::begin() const
{
	return _first;
}

iterator view::end() const
{
	return _last;
}

int view::compare(const view& other) const
{
	const auto lsize = _last - _first;
	const auto rsize = other._last - other._first;

	if (lsize < rsize) {
		return -1;
	} else if (lsize > rsize) {
		return 1;
	}

	// compare byte
	for (auto i = _first, j = other._first; i != _last; ++i, ++j) {
		const auto left  = *i;
		const auto right = *j;

		if (left < right) {
			return -1;
		} else if (left > right) {
			return 1;
		}
	}

	return 0;
}

bool view::operator==(const view& other) const
{
	return compare(other) == 0;
}

bool view::operator!=(const view& other) const
{
	return compare(other) != 0;
}

bool view::operator<(const view& other) const
{
	return compare(other) < 0;
}

bool view::operator>(const view& other) const
{
	return compare(other) > 0;
}

bool view::operator<=(const view& other) const
{
	return compare(other) <= 0;
}

bool view::operator>=(const view& other) const
{
	return compare(other) >= 0;
}
