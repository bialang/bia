#ifndef BIA_UTIL_PORTABLE_MEMORY_HPP_
#define BIA_UTIL_PORTABLE_MEMORY_HPP_

#include "../config.hpp"
#include "../gsl.hpp"

#include <algorithm>
#include <cstring>
#include <type_traits>

namespace bia {
namespace util {
namespace portable {

template<typename T>
void write(not_null<void*> memory, T value)
{
	typedef typename std::decay<T>::type type;

	static_assert(std::is_trivial<type>::value, "must be a trivial type");

	const auto ptr = static_cast<byte*>(memory.get());

	std::memcpy(ptr, &value, sizeof(val));

#if BIA_ENDIAN == BIA_BIG_ENDIAN
	std::reverse(ptr, ptr + sizeof(val));
#endif
}

template<typename T>
typename std::decay<T>::type read(not_null<const void*> memory)
{
	typedef typename std::decay<T>::type type;

	static_assert(std::is_trivial<type>::value, "must be a trivial type");

	type val{};
	const auto ptr = memory.get();

	std::memcpy(&val, ptr, sizeof(val));

#if BIA_ENDIAN == BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<byte*>(&val), reinterpret_cast<byte*>(&val) + sizeof(val));
#endif

	return val;
}

} // namespace portable
} // namespace util
} // namespace bia

#endif