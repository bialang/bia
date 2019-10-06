#pragma once

#include <cstddef>
#include <utility>

namespace bia {
namespace util {

inline std::size_t iterator_finished_index(bool* state)
{
	return 0;
}

template<typename Iterator, typename... Others>
inline std::size_t iterator_finished_index(bool* state, Iterator&& begin, Iterator&& end, Others&&... others)
{
	// success
	if (!*state && begin == end) {
		return 0;
	}

	return iterator_finished_index(state + 1, std::forward<Others>(others)...) + 1;
}

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

	constexpr auto size = sizeof...(Others) / 2;
	bool state[size]{};
	std::size_t equals = size;

	while (begin != end) {
		equals -= iterator_equals_helper(state, *begin, std::forward<Others>(others)...);

		if (!equals) {
			return size;
		}

		++begin;
	}

	return iterator_finished_index(state, std::forward<Others>(others)...);
}

template<typename T>
inline std::size_t iterator_starts_with_helper(bool* state, T&& value) noexcept
{
	return 0;
}

template<typename T, typename Iterator, typename... Others>
inline std::size_t iterator_starts_with_helper(bool* state, T&& value, Iterator&& begin, Iterator&& end,
											   Others&&... others)
{
	if (!*state) {
		// finished
		if (begin == end) {
			return 0;
		} else if (value != *begin) {
			*state = true;
		} else {
			++begin;
		}
	}

	return iterator_starts_with_helper(state + 1, std::forward<T>(value), std::forward<Others>(others)...) + 1;
}

template<typename Iterator, typename... Others>
inline std::pair<std::size_t, Iterator> iterator_starts_with(Iterator begin, Iterator end, Others... others)
{
	static_assert(sizeof...(Others) % 2 == 0, "others must be a pair of iterators");

	constexpr auto size = sizeof...(Others) / 2;
	bool state[size]{};
	std::size_t starts_with = size;

	while (begin != end) {
		auto index = iterator_starts_with_helper(state, *begin, std::forward<Others>(others)...);

		// finished
		if (index != size) {
			return { index, begin };
		}

		++begin;
	}

	return { iterator_finished_index(state, std::forward<Others>(others)...), begin };
}

} // namespace util
} // namespace bia