#pragma once

#include <cstring>
#include <cstdint>
#include <regex>
#include <type_traits>

#include "config.hpp"
#include "interpreter_rule.hpp"
#include "interpreter_id.hpp"
#include "input_stream.hpp"
#include "utf.hpp"


namespace bia
{
namespace grammar
{

enum STRING_CUSTOM_PARAMETER_FLAGS : uint64_t
{
	SCPF_RAW_STRING = 1ull << 63,
	SCPF_MASK = 0xffffffffull
};

template<size_t _Size>
inline bool fast_find(char _what, const char * _sorted_string) noexcept
{
	for (auto i = _sorted_string + _Size; _sorted_string < i; ++_sorted_string) {
		if (_what == *_sorted_string) {
			return true;
		}
	}

	return false;
}

inline int determine_base(const char *& _buffer, size_t & _length) noexcept
{
	if (*_buffer == '0') {
		if (_length > 1) {
			_buffer += 2;
			_length -= 2;

			// Binary
			if (_buffer[1] == 'b') {
				return 2;
			}
			// Hexadecimal
			else if (_buffer[1] == 'x') {
				return 16;
			}
			// Octal
			else if (_buffer[1] == 'o') {
				return 8;
			}
		}
	}

	return 10;
}

inline size_t whitespace_skipper(const char * _buffer, size_t _length) noexcept
{
	const auto _start_length = _length;

	while (_length) {
		switch (*_buffer++) {
		case ' ':
		case '\t':
		case '\r':
			--_length;

			break;
		default:
			return _start_length - _length;
		}
	}

	return _start_length - _length;
}

inline size_t padding_skipper(const char * _buffer, size_t _length) noexcept
{
	const auto _start_length = _length;

	while (_length) {
		switch (*_buffer++) {
		case ' ':
		case '\t':
		case '\r':
		case '\n':
			--_length;

			break;
		default:
			return _start_length - _length;
		}
	}

	return _start_length - _length;
}

template<flag_type _Flags, bool _Begin>
inline bool whitespace_deleter(const char *& _buffer, size_t & _length, token_output & _output) noexcept
{
	if (_Begin && (_Flags & (STARTING_WHITESPACE_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN | STARTING_PADDING_TOKEN | STARTING_PADDING_OPTIONAL_TOKEN)) ||
		!_Begin && (_Flags & ENDING_WHITESPACE_TOKEN)) {
		constexpr auto SKIPPER = _Flags & (STARTING_PADDING_TOKEN | STARTING_PADDING_OPTIONAL_TOKEN) ? padding_skipper : whitespace_skipper;
		auto _whitespaces = SKIPPER(_buffer, _length);

		//Whitespace found
		if (_whitespaces) {
			_buffer += _whitespaces;
			_length -= _whitespaces;

			if (_Begin)
				_output.offset += _whitespaces;
			else
				_output.padding += _whitespaces;
		}
		//No whitespace found
		else if (_Begin && (_Flags & (STARTING_WHITESPACE_TOKEN | STARTING_PADDING_TOKEN)) ||
			!_Begin && (_Flags & ENDING_WHITESPACE_TOKEN)) {
			return false;
		}
	}

	return true;
}



template<flag_type _Flags, int _For_clarity = 0>
inline ACTION IdentifierToken(const char * p_pcBuffer, size_t p_iSize, token_param, token_output & p_output)
{
	constexpr auto SUCCESS = _Flags & FILLER_TOKEN ? (_Flags & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_Flags & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _Flags & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR;

	//Starting whitespaces
	if (!whitespace_deleter<_Flags, true>(p_pcBuffer, p_iSize, p_output))
		return ERROR;

	if (p_output.iTokenSize < p_iSize)
	{
		if ((p_pcBuffer[p_output.iTokenSize] >= 'a' && p_pcBuffer[p_output.iTokenSize] <= 'z') ||
			(p_pcBuffer[p_output.iTokenSize] >= 'A' && p_pcBuffer[p_output.iTokenSize] <= 'Z') ||
			p_pcBuffer[p_output.iTokenSize] == '_')
			++p_output.iTokenSize;
		else
			return ERROR;
	}
	else
		return ERROR;

	while (p_output.iTokenSize < p_iSize)
	{
		if ((p_pcBuffer[p_output.iTokenSize] >= 'a' && p_pcBuffer[p_output.iTokenSize] <= 'z') ||
			(p_pcBuffer[p_output.iTokenSize] >= 'A' && p_pcBuffer[p_output.iTokenSize] <= 'Z') ||
			(p_pcBuffer[p_output.iTokenSize] >= '0' && p_pcBuffer[p_output.iTokenSize] <= '9') ||
			p_pcBuffer[p_output.iTokenSize] == '_')
			++p_output.iTokenSize;
		else
			break;
	}

	return SUCCESS;
}

template<flag_type _Flags, int _For_clarity = 0>
inline ACTION StringValueToken(const char * p_pcBuffer, size_t p_iSize, token_param, token_output & p_output)
{
	constexpr auto SUCCESS = _Flags & FILLER_TOKEN ? (_Flags & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_Flags & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _Flags & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : (_Flags & LOOPING_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR);

	enum FLAGS : uint32_t
	{
		F_SINGLE_QUOTE = 0x1,	/**	If set ', otherwise ".	*/
		F_QUOTE_SET = 0x2,
		F_RAW_STRING = 0x4,
	};

	auto pcDelimitor = "";
	size_t iDelimitor = 0;
	uint32_t fFlags = 0;

	//Starting whitespaces
	if (!whitespace_deleter<_Flags, true>(p_pcBuffer, p_iSize, p_output))
		return ERROR;

	//Determine delimitor and quote
	while (p_iSize--)
	{
		++p_output.iBufferOffset;

		switch (*p_pcBuffer++)
		{
		case 'R':
			//Add 'R' to delimitor
			if (fFlags & F_QUOTE_SET)
				++iDelimitor;
			else if (!(fFlags & F_RAW_STRING))
				fFlags |= F_RAW_STRING;
			else
				return ERROR;

			break;
		case '"': //Double quote
			//No quote set yet
			if (!(fFlags & F_QUOTE_SET))
			{
				fFlags |= F_QUOTE_SET;

				//Terminate
				if (!(fFlags & F_RAW_STRING))
					goto gt_break;
				else
					pcDelimitor = p_pcBuffer;
			}
			//Add to delimitor
			else
				++iDelimitor;

			break;
		case '\'': //Single quote
			//No quote set yet
			if (!(fFlags & F_QUOTE_SET))
			{
				fFlags |= F_QUOTE_SET | F_SINGLE_QUOTE;

				//Terminate
				if (!(fFlags & F_RAW_STRING))
					goto gt_break;
				else
					pcDelimitor = p_pcBuffer;
			}
			//Add to delimitor
			else
				++iDelimitor;

			break;
		case '(':
			//Terminate delimitor
			if (fFlags & F_QUOTE_SET)
				goto gt_break;

			return ERROR;
		default:
			//Add delimitor
			if (fFlags & F_QUOTE_SET)
				++iDelimitor;
			else
				return ERROR;

			break;
		}
	}

gt_break:;

	//Raw string
	if (fFlags & F_RAW_STRING)
	{
		p_output.iCustom = SCPF_RAW_STRING;

		while (p_iSize--)
		{
			switch (*p_pcBuffer++)
			{
			case ')':
				//Check delimitor size + quote
				if (p_iSize < iDelimitor + 1)
					return ERROR;
				else if (!memcmp(pcDelimitor, p_pcBuffer, iDelimitor))
				{
					if (!(fFlags & F_SINGLE_QUOTE) && p_pcBuffer[iDelimitor] == '"' ||
						fFlags & F_SINGLE_QUOTE && p_pcBuffer[iDelimitor] == '\'')
					{
						p_output.iBufferPadding = iDelimitor + 2;

						return SUCCESS;
					}
				}
			default:
				++p_output.iTokenSize;

				break;
			}
		}
	}
	else
	{
		const auto cpcEnd = p_pcBuffer + p_iSize;
		const auto cpcBegin = p_pcBuffer;

		while (p_pcBuffer < cpcEnd)
		{
			try
			{
				switch (utf8::next(p_pcBuffer, cpcEnd))
				{
				case '\\':
					utf8::advance(p_pcBuffer, 1, cpcEnd);

					break;
				case '\'':
					if (fFlags & F_SINGLE_QUOTE)
					{
						p_output.iBufferPadding = 1;
						p_output.iTokenSize = p_pcBuffer - cpcBegin - 1;

						return SUCCESS;
					}
				case '"':
					if (!(fFlags & F_SINGLE_QUOTE))
					{
						p_output.iBufferPadding = 1;
						p_output.iTokenSize = p_pcBuffer - cpcBegin - 1;

						return SUCCESS;
					}
				default:
					break;
				}
			}
			catch (...)
			{
				return ERROR;
			}
		}
	}
	
	return ERROR;
}

template<flag_type _Flags>
inline ACTION CustomOperatorToken(const char * p_pcBuffer, size_t p_iSize, token_param, token_output & p_output)
{
	constexpr auto SUCCESS = _Flags & FILLER_TOKEN ? (_Flags & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_Flags & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _Flags & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : (_Flags & LOOPING_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR);

	//Starting whitespaces
	if (!whitespace_deleter<_Flags, true>(p_pcBuffer, p_iSize, p_output))
		return ERROR;

	if (p_iSize > 4)
		p_iSize = 4;

	for (auto i = p_pcBuffer; p_output.iTokenSize < p_iSize; ++i)
	{
		switch (*i)
		{
		case '*':
		case '/':
		case '%':
		case '+':
		case '-':
		case '!':
		case '~':
		case '^':
		case '&':
		case '|':
		case '$':
		case '#':
			++p_output.iTokenSize;

			break;
		case ' ':
		default:
			return p_output.iTokenSize ? SUCCESS : ERROR;
		}
	}

	return ERROR;
}

template<flag_type _Flags>
inline ACTION AssignOperatorToken(const char * p_pcBuffer, size_t p_iSize, token_param, token_output & p_output)
{
	constexpr auto SUCCESS = _Flags & FILLER_TOKEN ? (_Flags & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_Flags & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _Flags & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : (_Flags & LOOPING_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR);

	//Starting whitespaces
	if (!whitespace_deleter<_Flags, true>(p_pcBuffer, p_iSize, p_output))
		return ERROR;

	if (p_iSize > 4)
		p_iSize = 4;

	for (auto i = p_pcBuffer; p_output.iTokenSize++ < p_iSize; ++i)
	{
		switch (*i)
		{
		case '*':
		case '/':
		case '%':
		case '+':
		case '-':
		//case '!':
		case '~':
		case '^':
		case '&':
		case '|':
		case '$':
		case '#':
			break;
		case '=':
			return SUCCESS;
		default:
			return ERROR;
		}
	}

	return ERROR;
}

template<flag_type _Flags>
inline ACTION CompareOperatorToken(const char * p_pcBuffer, size_t p_iSize, token_param, token_output & p_output)
{
	constexpr auto SUCCESS = _Flags & FILLER_TOKEN ? (_Flags & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_Flags & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _Flags & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : (_Flags & LOOPING_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR);

	//Starting whitespaces
	if (!whitespace_deleter<_Flags, true>(p_pcBuffer, p_iSize, p_output))
		return ERROR;

	if (p_iSize >= 2)
	{
		switch (p_pcBuffer[0])
		{
		case '=':
		case '!':
			p_output.iTokenSize += 2;

			return p_pcBuffer[1] == '=' ? SUCCESS : ERROR;
		case '<':
		case '>':
			if (p_pcBuffer[1] == '=')
			{
				p_output.iTokenSize += 2;

				return SUCCESS;
			}
		default:
			break;
		}

		goto gt_check_one;
	}
	
	if (p_iSize >= 1)
	{
	gt_check_one:;

		switch (p_pcBuffer[0])
		{
		case '<':
		case '>':
			p_output.iTokenSize++;

			return SUCCESS;
		default:
			break;
		}
	}

	return ERROR;
}


class interpreter_token final
{
public:
	interpreter_token() = delete;
	/**
	 * Matches a number token.
	 *
	 * @since	3.64.127.716
	 * @date	9-Apr-18
	 *
	 * @param	_buffer	Defines the buffer that should be matched.
	 * @param	_length	Defines the length of the buffer.
	 * @param	_params	(Not used)	Defines additional interpreter information.
	 * @param	[out]	_output	Defines the token result.
	 *
	 * @return	Defines the success code. See ::ACTION.
	*/
	static ACTION number(stream::input_stream & _input, token_param _params, token_output & _output) noexcept;
	static ACTION string(stream::input_stream & _input, token_param _params, token_output & _output);
	/**
	 * Matches an identifier. An identifier conists of alphanumeric characters and an underscore without a leading number.
	 *
	 * @since 3.64.127.716
	 * @date 24-Apr-18
	 *
	 * @param [in] _input The input buffer.
	 * @param _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See stream::input_stream::available(), stream::input_stream::get_buffer() and stream::input_stream::skip().
	 *
	 * @return Defines the success code. See ::ACTION.
	*/
	static ACTION identifier(stream::input_stream & _input, token_param _params, token_output & _output);
	static ACTION assign_operator(stream::input_stream & _input, token_param _params, token_output & _output);
	static ACTION compare_operator(stream::input_stream & _input, token_param _params, token_output & _output);
	/**
	 * Matches a comment which starts with '#' and ends with a line feed.
	 *
	 * @since 3.64.127.716
	 * @date 24-Apr-18
	 *
	 * @param [in] _input The input buffer.
	 * @param _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See stream::input_stream::available(), stream::input_stream::get_buffer() and stream::input_stream::skip().
	 *
	 * @return Defines the success code. See ::ACTION.
	*/
	static ACTION comment(stream::input_stream & _input, token_param _params, token_output & _output) noexcept;
	/**
	 * Matches a commend terminator.
	 *
	 * @since 3.64.127.716
	 * @date 24-Apr-18
	 *
	 * @param [in] _input The input buffer.
	 * @param _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See stream::input_stream::available(), stream::input_stream::get_buffer() and stream::input_stream::skip().
	 *
	 * @return Defines the success code. See ::ACTION.
	*/
	static ACTION command_end(stream::input_stream & _input, token_param _params, token_output & _output) noexcept;
	/**
	 * Matches a keyword token.
	 *
	 * @since 3.64.127.716
	 * @date 24-Apr-18
	 *
	 * @tparam _Ty The keyword. See @file interpreter_id.hpp for all keywords and operators.
	 * @tparam _Flags Manipulating the behavior of this function. See @ref grammar::flags.
	 *
	 * @param [in] _input The input buffer.
	 * @param _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See stream::input_stream::available(), stream::input_stream::get_buffer() and stream::input_stream::skip().
	 *
	 * @return Defines the success code. See ::ACTION.
	*/
	template<typename _Ty, flags::flag_type _Flags = flags::none>
	static ACTION keyword(stream::input_stream & _input, token_param _params, token_output & _output)
	{
		constexpr auto success = _Flags & flags::filler_token ? (_Flags & flags::looping_token ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_Flags & flags::looping_token ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
		constexpr auto error = _Flags & flags::opt_token ? ACTION::DONT_REPORT : (_Flags & flags::looping_token ? ACTION::DONT_REPORT : ACTION::ERROR);

		static_assert(_Ty::length() <= BIA_MAX_KEYWORD_LENGTH, "Keyword length exceeded.");

		if (_input.available() >= _Ty::length()) {
			auto _buffer = _input.get_buffer();
			auto _keyword = _Ty::token();
			auto _length = _Ty::length();

			while (_params.encoder->has_next(_buffer.first, _buffer.second)) {
				if (_params.encoder->next(_buffer.first, _buffer.second) != *_keyword++) {
					break;
				}

				if (!--_length) {
					// Set output
					_output.content.type = report::TYPE::KEYWORD;
					_output.content.content.keyword = _Ty::string_id();

					// Move cursor
					_input.skip(_buffer.first);

					return success;
				}
			}
		}

		return error;
	}
	/**
	 * Matches a rule pointer token.
	 *
	 * @since 3.64.127.716
	 * @date 9-Apr-18
	 *
	 * @tparam _Rule The rule id. See @ref BIA_GRAMMAR_RULE.
	 * @tparam _Flags Manipulating the behavior of this function. See @ref grammar::flags.
	 *
	 * @param [in] _input The input buffer.
	 * @param _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See interpreter_rule::run_rule().
	 *
	 * @return Defines the success code. See ::ACTION.
	*/
	template<report::rule_type _Rule, flags::flag_type _Flags = flags::filler_token>
	static ACTION rule_pointer(stream::input_stream & _input, token_param _params, token_output & _output)
	{
		constexpr auto success = _Flags & flags::filler_token ? (_Flags & flags::looping_token ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_Flags & flags::looping_token ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
		constexpr auto error = _Flags & (flags::opt_token | flags::looping_token) ? ACTION::DONT_REPORT : ACTION::ERROR;

		//Starting whitespaces
		if (!whitespace_deleter<_Flags, true>(_input, _output)) {
			return error;
		}

		return _params.rules[_Rule].run_rule(_input, _params) ? success : error;
	}

private:
	 /*
	1: sign information
	2: float/double value
	3: float literal
	4: binary value
	5: hex value
	6: octal value
	7: decimal value
	*/
	const static std::regex _number_pattern;

	static int get_value(char _digit) noexcept;
	/**
	 * Parses the integer that was matched by interpreter_token::number().
	 *
	 * @remarks	Do not use this function to parse integers!
	 *
	 * @since	3.64.127.716
	 * @date	9-Apr-18
	 *
	 * @param	_number	Defines the data.
	 * @param	_length	Defines the length of the data.
	 * @param	_custom	Defines the custom data.
	 *
	 * @return	The parsed value.
	*/
	static int64_t parse_integer(const char * _number, size_t _length, report::custom_type _custom) noexcept;
	/**
	 * Parses the floating point that was matched by interpreter_token::number().
	 *
	 * @remarks	Do not use this function to parse floating point!
	 *
	 * @since	3.64.127.716
	 * @date	9-Apr-18
	 *
	 * @param	_number	Defines the data.
	 * @param	_length	Defines the length of the data.
	 * @param	_custom	Defines the custom data.
	 *
	 * @return	The parsed value.
	*/
	template<typename _Ty>
	static typename std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type parse_floating_point(const char * _number, size_t _length, report::custom_type _custom) noexcept
	{
		_Ty _result = static_cast<_Ty>(0.);
		size_t i = 0;

		// Before dot
		for (; i < _length; ++i) {
			if (_number[i] == '.') {
				++i;

				goto gt_after_dot;
			} else if (_number[i] != '\'') {
				_result = _result * static_cast<_Ty>(10.) + static_cast<float>(get_value(_number[i]));
			}
		}

	gt_after_dot:;
		// After dot
		for (_Ty _factor = static_cast<_Ty>(1.); i < _length; ++i) {
			if (_number[i] != '\'') {
				_factor /= static_cast<_Ty>(10.);
				_result = _result + static_cast<float>(get_value(_number[i])) / _factor;
			}
		}

		// Negative
		if (_custom & grammar::NI_NEGATIVE_NUMBER) {
			return _result * static_cast<_Ty>(-1.);
		}

		return _result;
	}
};

}
}