#ifndef BIA_PRIMITIVES_HPP_
#define BIA_PRIMITIVES_HPP_

#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>

namespace bia {

typedef bool Bool;
typedef std::uint8_t Byte;
typedef std::int8_t Int8;
typedef std::uint8_t UInt8;
typedef std::int16_t Int16;
typedef std::uint16_t UInt16;
typedef std::int32_t Int32;
typedef std::uint32_t UInt32;
typedef std::ptrdiff_t Int;
typedef typename std::make_unsigned<Int>::type UInt;
typedef std::int64_t Int64;
typedef std::uint64_t UInt64;

static_assert(sizeof(float) == 4, "Size of float must be 32 bit");
static_assert(sizeof(double) == 8, "Size of double must 64 bit");
typedef float Float32;
typedef double Float64;

typedef std::string String;

} // namespace bia

#endif
