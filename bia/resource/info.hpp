#ifndef BIA_RESOURCE_INFO_HPP_
#define BIA_RESOURCE_INFO_HPP_

#include <bia/util/limit_checker.hpp>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <utility>

namespace bia {
namespace resource {

enum class Type
{
	string,
	regex,
};

enum class Size_width
{
	size_8,
	size_16,
	size_32
};

inline std::pair<Type, Size_width> info_from(char c) noexcept
{
	return { static_cast<Type>((static_cast<unsigned char>(c) >> 2) & 0xf), static_cast<Size_width>(c & 0x3) };
}

inline char info_to(Type type, Size_width size_width) noexcept
{
	return static_cast<char>((static_cast<int>(type) << 2) | static_cast<int>(size_width));
}

inline std::pair<Size_width, int> size_width_of(std::size_t value) noexcept
{
	if (util::Limit_checker<std::uint8_t>::in_bounds(value)) {
		return { Size_width::size_8, 1 };
	} else if (util::Limit_checker<std::uint16_t>::in_bounds(value)) {
		return { Size_width::size_16, 2 };
	}
	return { Size_width::size_32, 4 };
}

} // namespace resource
} // namespace bia

#endif
