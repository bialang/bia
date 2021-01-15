#ifndef BIA_UTIL_LIMIT_CHECKER_HPP_
#define BIA_UTIL_LIMIT_CHECKER_HPP_

#include <limits>
#include <type_traits>

namespace bia {
namespace util {

template<typename Type, typename = void>
struct Limit_checker;

template<typename Type>
struct Limit_checker<Type, typename std::enable_if<std::is_unsigned<Type>::value>::type>
{
	template<typename Other>
	constexpr static bool in_bounds(Other value) noexcept
	{
		return value <= std::numeric_limits<Type>::max();
	}
};

template<typename Type>
struct Limit_checker<Type, typename std::enable_if<std::is_signed<Type>::value>::type>
{
	template<typename Other>
	constexpr static bool in_bounds(Other value) noexcept
	{
		return value >= std::numeric_limits<Type>::min() && value <= std::numeric_limits<Type>::max();
	}
};

} // namespace util
} // namespace bia

#endif
