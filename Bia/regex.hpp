#pragma once

#include <cstdint>
#include <cstddef>

#include "config.hpp"

#if !defined(BIA_USE_STD_REGEX)
#include <boost/regex.hpp>
#include <boost/regex/icu.hpp>
#else
#include <regex>
#endif


namespace bia
{
namespace dependency
{

class regex
{
public:
	regex(const uint8_t * _bytes, size_t _size);
	regex(const char * _string);
	regex(const char16_t * _string);
	regex(const char32_t * _string);
	regex(const regex & _copy) = delete;
	regex(regex && _move) = delete;
	~regex();
	bool matches(const char * _string) const;

private:
	/** The compiled pattern. */
#if !defined(BIA_USE_STD_REGEX)
	boost::u32regex _code;
#else
	std::basic_regex<uint32_t> _code;
#endif
};

}
}