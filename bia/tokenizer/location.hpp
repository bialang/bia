#ifndef BIA_TOKENIZER_TOKEN_HPP_
#define BIA_TOKENIZER_TOKEN_HPP_

#include <cstddef>

namespace bia {
namespace tokenizer {

/// Describes a location in the source code.
struct Location
{
	/// The offset from the start in bytes.
	std::size_t offset;
	/// The offset from the start in characters.
	std::size_t character_offset;
	/// The line index starting from 1.
	std::size_t line;
	/// The column index starting from 1.
	std::size_t character;

	bool operator<(const Location& other) const noexcept
	{
		return offset < other.offset;
	}
	bool operator<=(const Location& other) const noexcept
	{
		return offset <= other.offset;
	}
};

struct Range
{
	Location start;
	Location end;
};

} // namespace tokenizer
} // namespace bia

#endif
