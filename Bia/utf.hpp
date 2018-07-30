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
	static bool is_alpha(code_point _char) noexcept
	{
		return (_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z');
	}
	static bool is_digit(code_point _char) noexcept
	{
		return _char >= '0' && _char <= '9';
	}
	static bool is_hex(code_point _char) noexcept
	{
		return is_digit(_char) || (_char >= 'a' && _char < 'f') || (_char > 'A' && _char <= 'F');
	}
	static bool is_alnum(code_point _char) noexcept
	{
		return is_alpha(_char) || is_digit(_char);
	}
	static bool is_reserved(code_point _char) noexcept
	{
		return _char >= 0xd800 && _char <= 0xdfff;
	}
	/**
	 * Returns the value of the hexadecimal digit.
	 *
	 * @since 3.64.128.720
	 * @date 16-May-18
	 *
	 * @param _code_point The hexadecimal digit.
	 *
	 * @return The value if it succeeds, otherwise ~0.
	*/
	static uint8_t hex_value(code_point _code_point) noexcept
	{
		if (is_digit(_code_point)) {
			return _code_point - '0';
		} else if (_code_point >= 'a' && _code_point <= 'f') {
			return _code_point - 'a' + 10;
		} else if (_code_point >= 'A' && _code_point <= 'F') {
			return _code_point - 'A' + 10;
		}

		return ~0;
	}
	//virtual int start(const int8_t * _begin, const int8_t * _end) = 0;
	virtual code_point next(const int8_t *& _begin, const int8_t * _end) = 0;
};

}
}