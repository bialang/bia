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

template<typename Type>
inline void write(std::ostream& output, Type value)
{
	// reverse bytes
#if BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<char*>(&value), reinterpret_cast<char*>(&value) + sizeof(value));
#endif
	output.write(reinterpret_cast<char*>(&value), sizeof(value));
}

template<typename Type, typename... Others>
inline void write(std::ostream& output, Type&& value, Others&&... values)
{
	write(output, std::forward<Type>(value));
	write(output, std::forward<Others>(values)...);
}

template<typename Type>
inline Type read(std::istream& input)
{
	Type value{};
	input.read(reinterpret_cast<char*>(&value), sizeof(value));
#if BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<char*>(&value), reinterpret_cast<char*>(&value) + sizeof(value));
#endif
	return value;
}

template<typename Type>
inline Type read(span<const byte_type*>& input)
{
	if (input.size_bytes() < sizeof(Type)) {
		throw;
	}

	Type value{};
	std::memcpy(&value, input.data(), sizeof(Type));
	input = input.subspan(sizeof(Type));
#if BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<byte_type*>(&value), reinterpret_cast<byte_type*>(&value) + sizeof(Type));
#endif
	return value;
}

} // namespace portable
} // namespace util
} // namespace bia

#endif
