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
inline std::size_t iterator_finished_index(bool* state, Iterator&& iterator, Others&&... others)
{
	// success
	if (!*state && !iterator.has_next()) {
		return 0;
	}

	return iterator_finished_index(state + 1, std::forward<Others>(others)...) + 1;
}

template<typename T>
inline std::size_t iterator_starts_with_helper(bool* state, T&& value) noexcept
{
	return 0;
}

template<typename T, typename Iterator, typename... Others>
inline std::size_t iterator_starts_with_helper(bool* state, T&& value, Iterator&& iterator, Others&&... others)
{
	std::size_t lost = 0;

	if (!*state) {
		if (iterator.has_next()) {
			if (value != iterator.next()) {
				*state = true;
				lost   = 1;
			}
		}
	}

	return lost + iterator_starts_with_helper(state + 1, std::forward<T>(value), std::forward<Others>(others)...);
}

template<typename Iterator, typename... Others>
inline std::pair<std::size_t, Iterator> iterator_starts_with(Iterator iterator, Others... others)
{
	constexpr auto size = sizeof...(Others);
	bool state[size]{};
	std::size_t starts_with = size;

	while (iterator.has_next()) {
		auto tmp = iterator;

		starts_with -= iterator_starts_with_helper(state, iterator.next(), std::forward<Others>(others)...);

		if (!starts_with) {
			iterator = tmp;

			break;
		}
	}

	return { iterator_finished_index(state, std::forward<Others>(others)...), iterator };
}

} // namespace util
} // namespace bia