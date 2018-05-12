#pragma once

#include <cstdint>


namespace bia
{
namespace encoding
{

class utf
{
public:
	typedef int32_t code_point;

	virtual ~utf() noexcept = default;
	virtual void append(code_point _char, int8_t *& _begin, const int8_t * _end) = 0;
	virtual bool has_next(const int8_t * _begin, const int8_t * _end) noexcept = 0;
	static bool is_alpha(code_point _char)
	{
		return (_char >= 'a' && _char <= 'z') || (_char >= 'A'&&_char <= 'Z');
	}
	static bool is_digit(code_point _char)
	{
		return _char >= '0' && _char <= '9';
	}
	static bool is_alnum(code_point _char)
	{
		return is_alpha(_char) || is_digit(_char);
	}
	static bool is_reserved(code_point _char)
	{
		return _char >= 0xd800 && _char <= 0xdfff;
	}
	//virtual int start(const int8_t * _begin, const int8_t * _end) = 0;
	virtual code_point next(const int8_t *& _begin, const int8_t * _end) = 0;
};

}
}