#ifndef BIA_UTIL_PORTABLE_STREAM_HPP_
#define BIA_UTIL_PORTABLE_STREAM_HPP_

#include "../config.hpp"
#include "../gsl.hpp"

#include <algorithm>
#include <cstring>
#include <istream>
#include <ostream>
#include <utility>

namespace bia {
namespace util {
namespace portable {

template<typename T>
inline void write(std::ostream& output, T value)
{
	// reverse bytes
#if BIA_ENDIAN == BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<char*>(&value), reinterpret_cast<char*>(&value) + sizeof(value));
#endif

	output.write(reinterpret_cast<char*>(&value), sizeof(value));
}

template<typename T, typename... Ts>
inline void write(std::ostream& output, T&& value, Ts&&... values)
{
	write(output, std::forward<T>(value));
	write(output, std::forward<Ts>(values)...);
}

template<typename T>
inline T read(std::istream& input)
{
	T value{};

	input.read(reinterpret_cast<char*>(&value), sizeof(value));

#if BIA_ENDIAN == BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<char*>(&value), reinterpret_cast<char*>(&value) + sizeof(value));
#endif

	return value;
}

template<typename Type>
inline Type read(span<const byte*>& input)
{
	if (input.size_bytes() < sizeof(Type)) {
		throw;
	}

	Type value{};

	std::memcpy(&value, input.data(), sizeof(Type));

	input = input.subspan(sizeof(Type));

#if BIA_ENDIAN == BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<byte*>(&value), reinterpret_cast<byte*>(&value) + sizeof(Type));
#endif

	return value;
}

} // namespace portable
} // namespace util
} // namespace bia

#endif
