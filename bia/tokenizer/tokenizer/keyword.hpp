#pragma once

#include <cstddef>

namespace bia {
namespace tokenizer {

enum class KEYWORD
{
	LET,
	TRUE,
	FALSE
};

struct keyword_let
{
	constexpr static const char16_t* name() noexcept
	{
		return u"let";
	}
	constexpr static std::size_t length() noexcept
	{
		return 3;
	}
	constexpr static KEYWORD keyword() noexcept
	{
		return KEYWORD::LET;
	}
};

} // namespace tokenizer
} // namespace bia