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

template<typename Type>
void write(Not_null<void*> memory, Type value)
{
	typedef typename std::decay<Type>::type type;
	static_assert(std::is_trivial<type>::value, "must be a trivial type");

	const auto ptr = static_cast<byte_type*>(memory.get());
	std::memcpy(ptr, &value, sizeof(value));
#if BIA_BIG_ENDIAN
	std::reverse(ptr, ptr + sizeof(value));
#endif
}

template<typename Type>
typename std::decay<Type>::type read(Not_null<const void*> memory)
{
	typedef typename std::decay<Type>::type type;
	static_assert(std::is_trivial<type>::value, "must be a trivial type");

	type val{};
	const auto ptr = memory.get();
	std::memcpy(&val, ptr, sizeof(val));
#if BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<byte_type*>(&val), reinterpret_cast<byte_type*>(&val) + sizeof(val));
#endif
	return val;
}

} // namespace portable
} // namespace util
} // namespace bia

#endif
