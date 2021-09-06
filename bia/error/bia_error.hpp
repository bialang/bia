#ifndef BIA_ERROR_BIA_ERROR_HPP_
#define BIA_ERROR_BIA_ERROR_HPP_

#include "code.hpp"

#include <cstddef>

namespace bia {
namespace error {

/// Describes a location in the Bia source code.
struct Bia_location
{
	/// The offset from the start in bytes.
	std::size_t offset;
	/// The offset from the start in characters.
	std::size_t character_offset;
	/// The line index starting from 1.
	std::size_t line;
	/// The column index starting from 1.
	std::size_t character;

	bool operator<(const Bia_location& other) const noexcept
	{
		return offset < other.offset;
	}
	bool operator<=(const Bia_location& other) const noexcept
	{
		return offset <= other.offset;
	}
};

/// A range in the Bia source code.
struct Bia_range
{
	Bia_location start;
	Bia_location end;
};

/// Describing an error in the Bia source code.
struct Bia
{
	std::error_code code;
	Bia_range range;

	Bia() noexcept : code{ error::Code::success }, range{}
	{}
	Bia(error::Code code, Bia_range range) noexcept : code{ code }, range{ range }
	{}
	bool operator==(error::Code code) const noexcept
	{
		return this->code == code;
	}
	bool operator!=(error::Code code) const noexcept
	{
		return this->code != code;
	}
	bool operator<(const Bia& other) const noexcept
	{
		return range.start < other.range.start;
	}
	operator bool() const noexcept
	{
		return code != error::Code::success;
	}
};

} // namespace error
} // namespace bia

#endif
