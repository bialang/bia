#ifndef BIA_UTIL_AGGREGATE_HPP_
#define BIA_UTIL_AGGREGATE_HPP_

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

} // namespace util
} // namespace bia

#endif
