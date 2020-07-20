#ifndef BIA_RESOURCE_INFO_HPP_
#define BIA_RESOURCE_INFO_HPP_

#include <cstddef>
#include <cstdint>
#include <limits>
#include <bia/util/limit_checker.hpp>
#include <utility>

namespace bia {
namespace resource {

enum class type
{
	string,
	regex,
	function
};

enum class size_width
{
	_8,
	_16,
	_32
};

inline std::pair<type, size_width> info_from(char c) noexcept
{
	return { static_cast<type>((c >> 2) & 0x1), static_cast<size_width>(c & 0x3) };
}

inline char info_to(type type, size_width size_width) noexcept
{
	return static_cast<char>((static_cast<int>(type) << 2) | static_cast<int>(size_width));
}

inline std::pair<size_width, int> size_width_of(std::size_t value) noexcept
{
	if (util::limit_checker<std::uint8_t>::in_bounds(value)) {
		return { size_width::_8, 1 };
	} else if (util::limit_checker<std::uint16_t>::in_bounds(value)) {
		return { size_width::_16, 2 };
	}

	return { size_width::_32, 4 };
}

} // namespace resource
} // namespace bia

#endif
