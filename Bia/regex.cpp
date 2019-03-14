#include "regex.hpp"

#include <string>


namespace bia
{
namespace dependency
{

regex::regex(const uint8_t * _bytes, size_t _size) : _code(boost::make_u32regex(_bytes, _bytes + _size, boost::regex_constants::perl))
{
}

regex::regex(const char * _string) : _code(boost::make_u32regex(_string, _string + std::char_traits<char>::length(_string), boost::regex_constants::perl))
{
}

regex::regex(const char16_t * _string) : _code(boost::make_u32regex(_string, _string + std::char_traits<char16_t>::length(_string), boost::regex_constants::perl))
{
}

regex::regex(const char32_t * _string) : _code(boost::make_u32regex(_string, _string + std::char_traits<char32_t>::length(_string), boost::regex_constants::perl))
{
}

regex::~regex()
{
}

bool regex::matches(const char * _string) const
{
	return boost::u32regex_match(_string, _code);
}

}
}