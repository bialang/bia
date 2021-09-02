#ifndef BIA_TOKENIZER_TOKEN_ERROR_INFO_HPP_
#define BIA_TOKENIZER_TOKEN_ERROR_INFO_HPP_

#include "../location.hpp"

#include <bia/error/code.hpp>

namespace bia {
namespace tokenizer {
namespace token {

struct Error_info
{
	error::Code code = error::Code::success;
	Range range{};

	bool operator<(const Error_info& other) const noexcept
	{
		return range.start < other.range.start;
	}
	bool operator==(error::Code code) const noexcept
	{
		return this->code == code;
	}
	bool operator!=(error::Code code) const noexcept
	{
		return this->code != code;
	}
	operator bool() const noexcept
	{
		return code != error::Code::success;
	}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
