#ifndef BIA_UTIL_AGGREGATE_HPP_
#define BIA_UTIL_AGGREGATE_HPP_

namespace bia {
namespace util {

template<typename Type>
constexpr inline Type min(Type value)
{
	return value;
}

template<typename Type, typename... Others>
constexpr inline Type min(Type value, Type other, Others... others)
{
	return value < min(other, others...) ? value : min(other, others...);
}

template<typename Type>
constexpr inline Type max(Type value)
{
	return value;
}

template<typename Type, typename... Others>
constexpr inline Type max(Type value, Type other, Others... others)
{
	return value > max(other, others...) ? value : max(other, others...);
}

} // namespace util
} // namespace bia

#endif
