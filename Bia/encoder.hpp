#pragma once

#include <cstdint>


namespace bia
{
namespace encoding
{

/** A 32 bit Unicode cope point. */
typedef int32_t code_point;

/**
 * @brief A encoder interface
 *
 * description
 *
 * @see @ref ascii, @ref utf8
*/
class encoder
{
public:
	/** The end-of-string code point. */
	static constexpr code_point eos = 0;

	/**
	 * Destructor.
	 *
	 * @since 3.68.140.789
	 * @date 26-Oct-18
	*/
	virtual ~encoder() noexcept = default;
	virtual void append(code_point _code_point, int8_t *& _begin, const int8_t * _end) = 0;
	virtual bool has_next(const int8_t * _begin, const int8_t * _end) noexcept = 0;
	/**
	 * Checks whether the code point is an alphabetic character or not.
	 *
	 * @since 3.68.140.789
	 * @date 26-Oct-18
	 *
	 * @param _code_point The code point.
	 *
	 * @return true if the code point is an alphabetic character, otherwise false.
	*/
	static bool is_alpha(code_point _code_point) noexcept
	{
		return (_code_point >= 'a' && _code_point <= 'z') || (_code_point >= 'A' && _code_point <= 'Z') || _code_point == 246;
	}
	static bool is_digit(code_point _code_point) noexcept
	{
		return _code_point >= '0' && _code_point <= '9';
	}
	static bool is_hex(code_point _code_point) noexcept
	{
		return is_digit(_code_point) || (_code_point >= 'a' && _code_point < 'f') || (_code_point > 'A' && _code_point <= 'F');
	}
	static bool is_alnum(code_point _code_point) noexcept
	{
		return is_alpha(_code_point) || is_digit(_code_point);
	}
	/**
	 * Checks whether the code point is a reserved character.
	 *
	 * @since 3.68.140.789
	 * @date 26-Oct-18
	 *
	 * @param _code_point The code point.
	 *
	 * @return true if it is a reserved character, otherwise false.
	*/
	static bool is_reserved(code_point _code_point) noexcept
	{
		return _code_point >= 0xd800 && _code_point <= 0xdfff;
	}
	/**
	 * Returns the value of the hexadecimal digit.
	 *
	 * @since 3.64.128.720
	 * @date 16-May-18
	 *
	 * @param _code_point The hexadecimal digit.
	 *
	 * @return The value if it succeeds, otherwise 0xff.
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

		return 0xff;
	}
	virtual code_point next(const int8_t *& _begin, const int8_t * _end) = 0;
	virtual code_point peek(const int8_t * _begin, const int8_t * _end) = 0;
};

}
}