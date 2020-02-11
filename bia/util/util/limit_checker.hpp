#ifndef BIA_UTIL_LIMIT_CHECKER_HPP_
#define BIA_UTIL_LIMIT_CHECKER_HPP_

#include <limits>
#include <type_traits>

namespace bia {
namespace util {

template<typename T, typename = void>
struct limit_checker;

template<typename T>
struct limit_checker<T, typename std::enable_if<std::is_unsigned<T>::value>::type>
{
	template<typename V>
	constexpr static bool in_bounds(V value) noexcept
	{
		return value <= std::numeric_limits<T>::max();
	}
};

template<typename T>
struct limit_checker<T, typename std::enable_if<std::is_signed<T>::value>::type>
{
	template<typename V>
	constexpr static bool in_bounds(V value) noexcept
	{
		return value >= std::numeric_limits<T>::min() && value <= std::numeric_limits<T>::max();
	}
};

} // namespace util
} // namespace bia

#endif