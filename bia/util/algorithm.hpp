#ifndef BIA_UTIL_ALGORITHM_HPP_
#define BIA_UTIL_ALGORITHM_HPP_

#include "contract.hpp"

#include <iterator>
#include <type_traits>
#include <utility>

namespace bia {
namespace util {

template<typename Type>
constexpr Type min(Type value) noexcept
{
	return value;
}

template<typename Type, typename... Others>
constexpr Type min(Type value, Type other, Others... others) noexcept
{
	return value < min(other, others...) ? value : min(other, others...);
}

template<typename Type>
constexpr Type max(Type value)
{
	return value;
}

template<typename Type, typename... Others>
constexpr Type max(Type value, Type other, Others... others) noexcept
{
	return value > max(other, others...) ? value : max(other, others...);
}

template<typename Left, typename Right>
constexpr int compare(Left&& left, Right&& right) noexcept
{
	return left < right ? -1 : (left == right ? 0 : 1);
}

template<typename Left, typename Right, typename... Others>
inline typename std::enable_if<(sizeof...(Others) >= 2), int>::type compare(Left&& left, Right&& right,
                                                                            Others&&... others) noexcept
{
	const int n = compare(std::forward<Left>(left), std::forward<Right>(right));
	return n == 0 ? compare(std::forward<Others>(others)...) : n;
}

template<typename RandomIterator1, typename RandomIterator2, typename Comparator>
inline int compare_ranges(RandomIterator1 first1, RandomIterator1 last1, RandomIterator2 first2,
                          RandomIterator2 last2, Comparator comparator)
{
	BIA_EXPECTS(first1 <= last1);
	BIA_EXPECTS(first2 <= last2);
	if (const int n = compare(std::distance(first1, last1), std::distance(first2, last2))) {
		return n;
	}
	for (; first1 != last1; ++first1, ++first2) {
		if (const int n = comparator(*first1, *first2)) {
			return n;
		}
	}
	return 0;
}

template<typename RandomIterator1, typename RandomIterator2>
inline int compare_ranges(RandomIterator1 first1, RandomIterator1 last1, RandomIterator2 first2,
                          RandomIterator2 last2)
{
	return compare_ranges(first1, last1, first2, last2, &compare<decltype(*first1), decltype(*first2)>);
}

} // namespace util
} // namespace bia

#endif
