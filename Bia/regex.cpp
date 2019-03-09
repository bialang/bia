#include "regex.hpp"
#include "internal_config.hpp"

#include <pcre2.h>


namespace bia
{
namespace dependency
{

regex::regex(const uint8_t * _bytes, size_t _size)
{
	int _error_code = 0;
	size_t _error_offset = 0;

	pcre2_compile_8(_bytes, _size, PCRE2_NEVER_UCP | PCRE2_NEVER_UTF, &_error_code, &_error_offset, nullptr);
}

regex::regex(const char * _string)
{
	int _error_code = 0;
	size_t _error_offset = 0;

	pcre2_compile_8(reinterpret_cast<PCRE2_SPTR8>(_string), PCRE2_ZERO_TERMINATED, PCRE2_UTF | PCRE2_NO_UTF_CHECK, &_error_code, &_error_offset, nullptr);
}

regex::regex(const char16_t * _string)
{
	int _error_code = 0;
	size_t _error_offset = 0;

	pcre2_compile_16(reinterpret_cast<PCRE2_SPTR16>(_string), PCRE2_ZERO_TERMINATED, PCRE2_UTF | PCRE2_NO_UTF_CHECK, &_error_code, &_error_offset, nullptr);
}

regex::regex(const char32_t * _string)
{
	int _error_code = 0;
	size_t _error_offset = 0;

	pcre2_compile_32(reinterpret_cast<PCRE2_SPTR32>(_string), PCRE2_ZERO_TERMINATED, PCRE2_UTF | PCRE2_NO_UTF_CHECK, &_error_code, &_error_offset, nullptr);
}

}
}