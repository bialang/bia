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

	_code = pcre2_compile_8(_bytes, _size, PCRE2_NEVER_UCP | PCRE2_NEVER_UTF, &_error_code, &_error_offset, nullptr);
	_type = TYPE::BYTE;
}

regex::regex(const char * _string)
{
	int _error_code = 0;
	size_t _error_offset = 0;

	_code = pcre2_compile_8(reinterpret_cast<PCRE2_SPTR8>(_string), PCRE2_ZERO_TERMINATED, PCRE2_UTF | PCRE2_NO_UTF_CHECK, &_error_code, &_error_offset, nullptr);
	_type = TYPE::UTF8;
}

regex::regex(const char16_t * _string)
{
	int _error_code = 0;
	size_t _error_offset = 0;

	_code = pcre2_compile_16(reinterpret_cast<PCRE2_SPTR16>(_string), PCRE2_ZERO_TERMINATED, PCRE2_UTF | PCRE2_NO_UTF_CHECK, &_error_code, &_error_offset, nullptr);
	_type = TYPE::UTF16;
}

regex::regex(const char32_t * _string)
{
	int _error_code = 0;
	size_t _error_offset = 0;

	_code = pcre2_compile_32(reinterpret_cast<PCRE2_SPTR32>(_string), PCRE2_ZERO_TERMINATED, PCRE2_UTF | PCRE2_NO_UTF_CHECK, &_error_code, &_error_offset, nullptr);
	_type = TYPE::UTF32;
}

regex::~regex()
{
	switch (_type) {
	case TYPE::BYTE:
	case TYPE::UTF8:
		pcre2_code_free_8(static_cast<pcre2_code_8*>(_code));

		break;
	case TYPE::UTF16:
		pcre2_code_free_16(static_cast<pcre2_code_16*>(_code));

		break;
	case TYPE::UTF32:
		pcre2_code_free_32(static_cast<pcre2_code_32*>(_code));

		break;
	default:
		break;
	}
}

bool regex::matches(const char * _string) const
{
	auto _data = pcre2_match_data_create_from_pattern_8(static_cast<pcre2_code_8*>(_code), nullptr);
	auto _matches = pcre2_match_8(static_cast<pcre2_code_8*>(_code), (PCRE2_SPTR8)_string, PCRE2_ZERO_TERMINATED, 0, PCRE2_ANCHORED, _data, nullptr) > 0;

	pcre2_match_data_free_8(_data);

	return _matches;
}

}
}