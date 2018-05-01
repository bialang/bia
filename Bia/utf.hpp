#pragma once

#include <cstdint>


namespace bia
{
namespace encoding
{

class utf
{
public:
	typedef int32_t char_type;

	virtual ~utf() noexcept = default;
	virtual void append(char_type _char, int8_t *& _begin, const int8_t * _end) = 0;
	virtual bool has_next(const int8_t * _begin, const int8_t * _end) noexcept = 0;
	static bool is_alpha(char_type _char)
	{
		return (_char >= 'a' && _char <= 'z') || (_char >= 'A'&&_char <= 'Z');
	}
	static bool is_digit(char_type _char)
	{
		return _char >= '0' && _char <= '9';
	}
	static bool is_alnum(char_type _char)
	{
		return is_alpha(_char) || is_digit(_char);
	}
	static bool is_reserved(char_type _char)
	{
		return _char >= 0xd800 && _char <= 0xdfff;
	}
	virtual int start(const int8_t * _begin, const int8_t * _end) = 0;
	virtual char_type next(const int8_t *& _begin, const int8_t * _end) = 0;
};

}
}