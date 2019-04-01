#pragma once

#include <cstdint>
#include <cstddef>

#include "config.hpp"
#include "string_stream.hpp"

#if !defined(BIA_USE_STD_REGEX)
#include <boost/regex.hpp>
#include <boost/regex/icu.hpp>
#else
#include <regex>
#endif


namespace bia
{
namespace detail
{

class regex
{
public:
	typedef stream::string_stream::length_t length_t;

	regex(const char * _string, length_t _length);
	regex(const char16_t * _string, length_t _length);
	regex(const char32_t * _string, length_t _length);
	regex(const regex & _copy) = delete;
	regex(regex && _move) = delete;
	~regex();

	bool matches(const char * _string, length_t _length) const;
	bool matches(const char16_t * _string, length_t _length) const;
	bool matches(const char32_t * _string, length_t _length) const;
	bool contains(const char * _string, length_t _length) const;
	bool contains(const char16_t * _string, length_t _length) const;
	bool contains(const char32_t * _string, length_t _length) const;

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