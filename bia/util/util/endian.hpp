#pragma once

#include <bia/config.hpp>
#include <type_traits>

namespace bia {
namespace util {

template<typename T>
inline typename std::enable_if<std::is_integral<T>::value, T>::type from_big_endian(const void* ptr)
{
#if defined(BIA_BIG_ENDIAN)
	return *static_cast<const T*>(ptr);
#elif defined(BIA_LITTLE_ENDIAN)

#endif
}

template<typename T>
inline typename std::enable_if<std::is_integral<T>::value, T>::type from_little_endian(const void* ptr)
{
#if defined(BIA_BIG_ENDIAN)
#elif defined(BIA_LITTLE_ENDIAN)
	return *static_cast<const T*>(ptr);
#endif
}

} // namespace util
} // namespace bia