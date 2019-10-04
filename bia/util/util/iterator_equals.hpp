#pragma once

#include <cstddef>
#include <utility>

namespace bia {
namespace util {

template<typename T>
inline std::size_t iterator_equals_helper(bool* state, T&& value) noexcept
{
	return 0;
}

template<typename T, typename Iterator, typename... Others>
inline std::size_t iterator_equals_helper(bool* state, T&& value, Iterator&& begin, Iterator&& end, Others&&... others)
{
	std::size_t lost = 0;

	if (!*state) {
		if (begin == end || value != *begin) {
			*state = true;
			lost   = 1;
		} else {
			++begin;
		}
	}

	return lost + iterator_equals_helper(state + 1, std::forward<T>(value), std::forward<Others>(others)...);
}

template<typename Iterator, typename... Others>
inline std::size_t iterator_equals(Iterator begin, Iterator end, Others... others)
{
	static_assert(sizeof...(Others) % 2 == 0, "others must be a pair of iterators");

	bool state[sizeof...(Others) / 2]{};
	std::size_t equals = sizeof...(Others) / 2;

	while (begin != end && equals) {
		equals -= iterator_equals_helper(state, *begin, std::forward<Others>(others)...);

		++begin;
	}

	return equals;
}

} // namespace util
} // namespace bia