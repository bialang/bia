#ifndef BIA_TOKENIZER_TOKEN_ERROR_INFO_HPP_
#define BIA_TOKENIZER_TOKEN_ERROR_INFO_HPP_

#include <bia/error/code.hpp>

namespace bia {
namespace tokenizer {
namespace token {

struct error_info
{
	error::code code = error::code::success;
	std::size_t line;
	std::size_t column;
	/// the offset in bytes
	std::size_t offset;
	/// the length of the error token
	std::size_t length;

	bool operator<(const error_info& other) const noexcept
	{
		return offset < other.offset;
	}
	operator bool() const noexcept
	{
		return code != error::code::success;
	}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif