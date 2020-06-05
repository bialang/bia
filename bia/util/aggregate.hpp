#ifndef BIA_UTIL_AGGREGATE_HPP_
#define BIA_UTIL_AGGREGATE_HPP_

namespace bia {
namespace util {

template<typename T>
constexpr inline T min(T value)
{
	return value;
}

template<typename T, typename... Ts>
constexpr inline T min(T value, T other, Ts... others)
{
	return value < min(other, others...) ? value : min(other, others...);
}

template<typename T>
constexpr inline T max(T value)
{
	return value;
}

template<typename T, typename... Ts>
constexpr inline T max(T value, T other, Ts... others)
{
	return value > max(other, others...) ? value : max(other, others...);
}

} // namespace util
} // namespace bia

#endif