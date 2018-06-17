#pragma once

#include <cstring>
#include <cstdint>
#include <type_traits>
#include <tuple>
#include <utility>

#include "config.hpp"
#include "interpreter_rule.hpp"
#include "interpreter_id.hpp"
#include "input_stream.hpp"
#include "utf.hpp"


namespace bia
{
namespace grammar
{

class interpreter_token final
{
public:
	interpreter_token() = delete;
	
	/**
	 * Matches all whitespace or padding characters it can.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @tparam _Flags The flags for the behavior.
	 * @tparam _Begin If this is called before or after the token.
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _encoder The encoder.
	 *
	 * @throws See padding_skipper() and whitespace_skipper().
	 *
	 * @return true if succeded according to the @a _Flags, otherwise false.
	*/
	template<flags::flag_type _Flags, bool _Begin>
	static bool whitespace_deleter(stream::input_stream & _input, encoding::utf * _encoder) noexcept
	{
		constexpr auto match_begin = _Begin && (_Flags & (flags::starting_ws_token | flags::starting_ws_opt_token | flags::starting_padding_token | flags::starting_padding_opt_token));
		constexpr auto match_end = !_Begin && (_Flags & (flags::ending_ws_token | flags::ending_ws_opt_token));

		if (match_begin || match_end) {
			constexpr auto skipper = _Flags & (flags::starting_padding_token | flags::starting_padding_opt_token) ? padding_skipper : whitespace_skipper;

			// No characters were skipped
			if (!skipper(_input, _encoder)) {
				// But they are required
				if (_Begin && (_Flags & (flags::starting_ws_token | flags::starting_padding_token)) || !_Begin && (_Flags & flags::ending_ws_token)) {
					return false;
				}
			}
		}

		return true;
	}
	/**
	 * Matches all whitespace characters it can.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _encoder The encoder.
	 *
	 * @throws See stream::input_stream::available(), stream::input_stream::get_buffer() and stream::input_stream::skip().
	 * @throws See encoding::utf::next().
	 *
	 * @return true if any whitespace was matched, otherwise false.
	*/
	static bool whitespace_skipper(stream::input_stream & _input, encoding::utf * _encoder);
	/**
	 * Matches all padding characters it can.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _encoder The encoder.
	 *
	 * @throws See stream::input_stream::available(), stream::input_stream::get_buffer() and stream::input_stream::skip().
	 * @throws See encoding::utf::next().
	 *
	 * @return true if any padding character was matched, otherwise false.
	*/
	static bool padding_skipper(stream::input_stream & _input, encoding::utf * _encoder);
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
	 * @return	Defines the success code. See @ref ACTION.
	*/
	static ACTION number(stream::input_stream & _input, token_param _params, token_output & _output);
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
	 * @throws See encoding::utf::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	static ACTION identifier(stream::input_stream & _input, token_param _params, token_output & _output);
	/**
	 * Matches an assign operator.
	 *
	 * @remarks	A leading whitespace is optional and will be consumed, if present.
	 *
	 * @since 3.64.127.716
	 * @date 24-Apr-18
	 *
	 * @param [in] _input The input buffer.
	 * @param _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_deleter().
	 * @throws See stream::input_stream::available(), stream::input_stream::get_buffer() and stream::input_stream::skip().
	 * @throws See encoding::utf::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	static ACTION assign_operator(stream::input_stream & _input, token_param _params, token_output & _output);
	/**
	 * Matches a compare operator.
	 *
	 * @remarks	A leading whitespace is optional and will be consumed, if present.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [in] _input The input buffer.
	 * @param _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_deleter().
	 * @throws See stream::input_stream::available(), stream::input_stream::get_buffer() and stream::input_stream::skip().
	 * @throws See encoding::utf::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	static ACTION compare_operator(stream::input_stream & _input, token_param _params, token_output & _output);
	/**
	 * Matches a dot operator like `*`, `/` and so on.
	 *
	 * @remarks	A leading whitespace is optional and will be consumed, if present.
	 *
	 * @since 3.64.132.729
	 * @date 15-Jun-18
	 *
	 * @param [in] _input The input buffer.
	 * @param _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_deleter().
	 * @throws See stream::input_stream::get_buffer() and stream::input_stream::skip().
	 * @throws See encoding::utf::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	static ACTION dot_operator(stream::input_stream & _input, token_param _params, token_output & _output);
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
	 * @throws See encoding::utf::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	static ACTION comment(stream::input_stream & _input, token_param _params, token_output & _output);
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
	 * @throws See encoding::utf::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	static ACTION command_end(stream::input_stream & _input, token_param _params, token_output & _output);
	/**
	 * Matches a custom operator.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @tparam _Flags Manipulating the behavior of this function. See @ref grammar::flags.
	 *
	 * @param [in] _input The input buffer.
	 * @param _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_deleter().
	 * @throws See stream::input_stream::available(), stream::input_stream::get_buffer() and stream::input_stream::skip().
	 * @throws See encoding::utf::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	template<flags::flag_type _Flags>
	static ACTION custom_operator(stream::input_stream & _input, token_param _params, token_output & _output)
	{
		constexpr auto success = _Flags & flags::filler_token ? (_Flags & flags::looping_token ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_Flags & flags::looping_token ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
		constexpr auto error = _Flags & (flags::opt_token | flags::looping_token) ? ACTION::DONT_REPORT : ACTION::ERROR;

		// Starting whitespaces
		if (!whitespace_deleter<_Flags, true>(_input, _params.encoder)) {
			return error;
		}

		if (_input.available() > 0) {
			auto _max = BIA_MAX_OPERATOR_LENGTH;
			auto _buffer = _input.get_buffer();
			auto _prev = _buffer.first;

			while (_max-- && _params.encoder->has_next(_buffer.first, _buffer.second)) {
				_prev = _buffer.first;
				auto _code_point = _params.encoder->next(_buffer.first, _buffer.second);

				switch (_code_point) {
				case '*':
				case '/':
				case '%':
				case '+':
				case '-':
				case '~':
				case '^':
				case '&':
				case '|':
				case '$':
					_output.content.content.operator_code = _output.content.content.operator_code << 8 | _code_point;

					break;
				default:
					goto gt_break;
				}
			}

		gt_break:;

			if (_output.content.content.operator_code) {
				_output.content.type = report::TYPE::OPERATOR_CODE;

				// Move cursor
				_input.skip(_prev);

				// Ending whitespaces
				if (!whitespace_deleter<_Flags, false>(_input, _params.encoder)) {
					return error;
				}

				return success;
			}
		}

		return error;
	}
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
	 * @throws See whitespace_deleter().
	 * @throws See stream::input_stream::available(), stream::input_stream::get_buffer() and stream::input_stream::skip().
	 * @throws See encoding::utf::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	template<typename _Ty, flags::flag_type _Flags = flags::none>
	static ACTION keyword(stream::input_stream & _input, token_param _params, token_output & _output)
	{
		constexpr auto success = _Flags & flags::filler_token ? (_Flags & flags::looping_token ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_Flags & flags::looping_token ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
		constexpr auto error = _Flags & (flags::opt_token | flags::looping_token) ? ACTION::DONT_REPORT : ACTION::ERROR;

		static_assert(_Ty::length() <= BIA_MAX_KEYWORD_LENGTH, "Keyword length exceeded.");

		// Starting whitespaces
		if (!whitespace_deleter<_Flags, true>(_input, _params.encoder)) {
			return error;
		}

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

					// Ending whitespaces
					if (!whitespace_deleter<_Flags, false>(_input, _params.encoder)) {
						return error;
					}

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
	 * @throws See whitespace_deleter().
	 * @throws See interpreter_rule::run_rule().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	template<report::rule_type _Rule, flags::flag_type _Flags = flags::filler_token>
	static ACTION rule_pointer(stream::input_stream & _input, token_param _params, token_output & _output)
	{
		constexpr auto success = _Flags & flags::filler_token ? (_Flags & flags::looping_token ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_Flags & flags::looping_token ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
		constexpr auto error = _Flags & (flags::opt_token | flags::looping_token) ? ACTION::DONT_REPORT : ACTION::ERROR;
		
		// Starting whitespaces
		if (!whitespace_deleter<_Flags, true>(_input, _params.encoder)) {
			return error;
		}

		if (_params.rules[_Rule].run_rule(_input, _params)) {
			// Ending whitespaces
			if (!whitespace_deleter<_Flags, false>(_input, _params.encoder)) {
				return error;
			}

			return success;
		}

		return error;
	}

private:
	/**
	 * Matches integral values with a base up to 16.
	 *
	 * @remarks The parameters are not checked.
	 *
	 * @since 3.64.128.720
	 * @date 16-May-18
	 *
	 * @param [in,out] _buffer The buffer.
	 * @param [in] _encoder The encoder.
	 * @param _base The base.
	 *
	 * @throws See encoding::utf::next().
	 *
	 * @return A pair with the success value as first and the parsed integral as second.
	*/
	static  std::pair<bool, int64_t> match_base(stream::input_stream::buffer_type & _buffer, encoding::utf * _encoder, int _base);
	/**
	 * Matches integral values with a base up to 16.
	 *
	 * @remarks The parameters are not checked.
	 *
	 * @since 3.64.130.722
	 * @date 16-May-18
	 *
	 * @param [in,out] _buffer The buffer.
	 * @param [in] _encoder The encoder.
	 *
	 * @throws See encoding::utf::next().
	 *
	 * @return A pair with the success value as first and the parsed integral as second.
	*/
	static  std::tuple<bool, int64_t, double, bool> match_decimal(stream::input_stream::buffer_type & _buffer, encoding::utf * _encoder);
};

}
}