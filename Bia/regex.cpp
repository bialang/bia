#include "regex.hpp"


namespace bia
{
namespace dependency
{

#if defined(BIA_USE_STD_REGEX)
#error "Not implemented."
#else

regex::regex(const char * _string, length_t _length) : _code(boost::make_u32regex(_string, _string + _length, boost::regex_constants::perl))
{
}

regex::regex(const char16_t * _string, length_t _length) : _code(boost::make_u32regex(_string, _string + _length, boost::regex_constants::perl))
{
}

regex::regex(const char32_t * _string, length_t _length) : _code(boost::make_u32regex(_string, _string + _length, boost::regex_constants::perl))
{
}

regex::~regex()
{
}

bool regex::matches(const char * _string, length_t _length) const
{
	return boost::u32regex_match(_string, _string + _length, _code);
}

bool regex::matches(const char16_t * _string, length_t _length) const
{
	return boost::u32regex_match(_string, _string + _length, _code);
}

bool regex::matches(const char32_t * _string, length_t _length) const
{
	return boost::u32regex_match(_string, _string + _length, _code);
}

bool regex::contains(const char * _string, length_t _length) const
{
	return boost::u32regex_search(_string, _string + _length, _code);
}

bool regex::contains(const char16_t * _string, length_t _length) const
{
	return boost::u32regex_search(_string, _string + _length, _code);
}

bool regex::contains(const char32_t * _string, length_t _length) const
{
	return boost::u32regex_search(_string, _string + _length, _code);
}

#endif

}
}