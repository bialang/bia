#pragma once

#include <cstring>
#include <cstdint>
#include <type_traits>
#include <tuple>
#include <utility>

#include "config.hpp"
#include "grammar_rule.hpp"
#include "grammar_id.hpp"
#include "buffer_input_stream.hpp"
#include "string_stream.hpp"
#include "encoder.hpp"


namespace bia
{
namespace grammar
{

class lexer_token final
{
public:
	lexer_token() = delete;

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
	template<flags::flag_t Flags, bool Called_at_beginning>
	static bool whitespace_deleter(stream::buffer_input_stream & _input, encoding::encoder * _encoder) noexcept
	{
		constexpr auto match_begin = Called_at_beginning && (Flags & (flags::starting_ws_token | flags::starting_ws_opt_token | flags::starting_padding_token | flags::starting_padding_opt_token));
		constexpr auto match_end = !Called_at_beginning && (Flags & (flags::ending_ws_token | flags::ending_ws_opt_token));

		if (match_begin || match_end) {
			constexpr auto skipper = Flags & (flags::starting_padding_token | flags::starting_padding_opt_token) ? padding_skipper : whitespace_skipper;

			// No characters were skipped
			if (!skipper(_input, _encoder)) {
				// But they are required
				if ((Called_at_beginning && (Flags & (flags::starting_ws_token | flags::starting_padding_token))) || (!Called_at_beginning && (Flags & flags::ending_ws_token))) {
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
	 * @throws See whitespace_automaton().
	 *
	 * @return true if any whitespace was matched, otherwise false.
	*/
	BIA_EXPORT static bool whitespace_skipper(stream::buffer_input_stream & _input, encoding::encoder * _encoder);
	/**
	 * Matches all padding characters it can.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _encoder The encoder.
	 *
	 * @throws See whitespace_automaton().
	 *
	 * @return true if any padding character was matched, otherwise false.
	*/
	BIA_EXPORT static bool padding_skipper(stream::buffer_input_stream & _input, encoding::encoder * _encoder);
	/**
	 * Matches a number token.
	 *
	 * @since 3.64.127.716
	 * @date 9-Apr-18
	 *
	 * @param _buffer Defines the buffer that should be matched.
	 * @param _length Defines the length of the buffer.
	 * @param [in] _params Defines additional interpreter information.
	 * @param [out]	_output Defines the token result.
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	BIA_EXPORT static ACTION number(stream::buffer_input_stream & _input, token_param & _params, token_output & _output);
	BIA_EXPORT static ACTION string(stream::buffer_input_stream & _input, token_param & _params, token_output & _output);
	BIA_EXPORT static ACTION regex(stream::buffer_input_stream & _input, token_param & _params, token_output & _output);
	/**
	 * Matches an identifier. An identifier conists of alphanumeric characters and an underscore without a leading number.
	 *
	 * @since 3.64.127.716
	 * @date 24-Apr-18
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See stream::buffer_input_stream::available(), stream::buffer_input_stream::buffer() and stream::buffer_input_stream::skip().
	 * @throws See encoding::encoder::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	BIA_EXPORT static ACTION identifier(stream::buffer_input_stream & _input, token_param & _params, token_output & _output);
	/**
	 * Matches the first member of a member chain.
	 *
	 * @since 3.67.135.749
	 * @date 6-Aug-18
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_deleter(), string(), keyword() and identifier().
	 * @throws See stream::buffer_input_stream::mark() and stream::buffer_input_stream::reset().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	BIA_EXPORT static ACTION first_member(stream::buffer_input_stream & _input, token_param & _params, token_output & _output);
	/**
	 * Matches an assign operator.
	 *
	 * @remarks	A leading whitespace is optional and will be consumed, if present.
	 *
	 * @since 3.64.127.716
	 * @date 24-Apr-18
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_deleter().
	 * @throws See stream::buffer_input_stream::available(), stream::buffer_input_stream::buffer() and stream::buffer_input_stream::skip().
	 * @throws See encoding::encoder::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	BIA_EXPORT static ACTION assign_operator(stream::buffer_input_stream & _input, token_param & _params, token_output & _output);
	/**
	 * Matches a compare operator.
	 *
	 * @remarks	A leading whitespace is optional and will be consumed, if present.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_deleter().
	 * @throws See stream::buffer_input_stream::available(), stream::buffer_input_stream::buffer() and stream::buffer_input_stream::skip().
	 * @throws See encoding::encoder::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	BIA_EXPORT static ACTION compare_operator(stream::buffer_input_stream & _input, token_param & _params, token_output & _output);
	/**
	 * Matches a dot operator like `*`, `/` and so on.
	 *
	 * @remarks	A leading whitespace is optional and will be consumed, if present.
	 *
	 * @since 3.64.132.729
	 * @date 15-Jun-18
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_deleter().
	 * @throws See stream::buffer_input_stream::buffer() and stream::buffer_input_stream::skip().
	 * @throws See encoding::encoder::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	BIA_EXPORT static ACTION dot_operator(stream::buffer_input_stream & _input, token_param & _params, token_output & _output);
	/**
	 * Matches a commend terminator.
	 *
	 * @since 3.64.127.716
	 * @date 24-Apr-18
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_automaton().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	BIA_EXPORT static ACTION command_end(stream::buffer_input_stream & _input, token_param & _params, token_output & _output);
	/**
	 * Matches a custom operator.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @tparam Flags Manipulating the behavior of this function. See @ref grammar::flags.
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_deleter().
	 * @throws See stream::buffer_input_stream::available(), stream::buffer_input_stream::buffer() and stream::buffer_input_stream::skip().
	 * @throws See encoding::encoder::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	template<flags::flag_t Flags>
	static ACTION custom_operator(stream::buffer_input_stream & _input, token_param & _params, token_output & _output)
	{
		constexpr auto success = Flags & flags::filler_token ? (Flags & flags::looping_token ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (Flags & flags::looping_token ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
		constexpr auto error = Flags & (flags::opt_token | flags::looping_token) ? ACTION::DONT_REPORT : ACTION::ERROR;

		// Starting whitespaces
		if (!whitespace_deleter<Flags, true>(_input, _params.encoder)) {
			return error;
		}

		if (_input.available() > 0) {
			auto _max = BIA_MAX_OPERATOR_LENGTH;
			auto _buffer = _input.buffer();
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
					_output.content.operator_code = _output.content.operator_code << 8 | _code_point;

					break;
				default:
					goto gt_break;
				}
			}

		gt_break:;

			if (_output.content.operator_code) {
				_output.type = report::TYPE::OPERATOR_CODE;

				// Move cursor
				_input.skip(_prev);

				// Ending whitespaces
				if (!whitespace_deleter<Flags, false>(_input, _params.encoder)) {
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
	 * @tparam Flags Manipulating the behavior of this function. See @ref grammar::flags.
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_deleter().
	 * @throws See stream::buffer_input_stream::available(), stream::buffer_input_stream::buffer() and stream::buffer_input_stream::skip().
	 * @throws See encoding::encoder::next().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	template<typename Type, flags::flag_t Flags = flags::none>
	static ACTION keyword(stream::buffer_input_stream & _input, token_param & _params, token_output & _output)
	{
		constexpr auto success = Flags & flags::filler_token ? (Flags & flags::looping_token ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (Flags & flags::looping_token ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
		constexpr auto error = Flags & (flags::opt_token | flags::looping_token) ? ACTION::DONT_REPORT : ACTION::ERROR;

		static_assert(Type::length() <= BIA_MAX_KEYWORD_LENGTH, "Keyword length exceeded.");

		// Starting whitespaces
		if (!whitespace_deleter<Flags, true>(_input, _params.encoder)) {
			return error;
		}

		if (_input.available() >= Type::length()) {
			auto _buffer = _input.buffer();
			auto _keyword = Type::token();
			auto _length = Type::length();

			while (_params.encoder->has_next(_buffer.first, _buffer.second)) {
				if (_params.encoder->next(_buffer.first, _buffer.second) != *_keyword++) {
					break;
				}

				if (!--_length) {
					// Set output
					_output.type = report::TYPE::KEYWORD;
					_output.content.keyword = Type::string_id();

					// Move cursor
					_input.skip(_buffer.first);

					// Ending whitespaces
					if (!whitespace_deleter<Flags, false>(_input, _params.encoder)) {
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
	 * @tparam Flags Manipulating the behavior of this function. See @ref grammar::flags.
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _params Additional interpreter information.
	 * @param [out] _output The token result.
	 *
	 * @throws See whitespace_deleter().
	 * @throws See interpreter_rule::run_rule().
	 *
	 * @return Defines the success code. See @ref ACTION.
	*/
	template<report::rule_t Rule, flags::flag_t Flags = flags::filler_token, report::custom_t Custom_parameter = 0>
	static ACTION rule_pointer(stream::buffer_input_stream & _input, token_param & _params, token_output & _output)
	{
		constexpr auto success = Flags & flags::looping_token ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT;
		constexpr auto error = Flags & (flags::opt_token | flags::looping_token) ? ACTION::DONT_REPORT : ACTION::ERROR;

		// Starting whitespaces
		if (!whitespace_deleter<Flags, true>(_input, _params.encoder)) {
			return error;
		} // Report this token
		else if (!(Flags & flags::filler_token)) {
			_output.type = report::TYPE::RULE_TOKEN;
			_output.custom_parameter = Custom_parameter;
			_output.token_id = _params.token_id;

			_params.bundle->add(_output);
		}

		if (_params.rules[Rule].run(_input, _params)) {
			// Ending whitespaces
			if (!whitespace_deleter<Flags, false>(_input, _params.encoder)) {
				return error;
			}

			return success;
		}

		return error;
	}

private:
	BIA_EXPORT static void match_big_integer(stream::buffer_input_stream & _input, stream::string_stream & _output, encoding::encoder * _encoder, int _base);
	/**
	 * Parses the sign before a number.
	 *
	 * @since 3.68.140.790
	 * @date 10-Nov-18
	 *
	 * @param [in] _buffer The input buffer.
	 * @param [in] _encoder The encoder.
	 *
	 * @throws See stream::buffer_input_stream::available(), stream::buffer_input_stream::buffer() and stream::buffer_input_stream::skip().
	 * @throws See encoding::encoder::next().
	 *
	 * @return true if the sign is negative, otherwise false.
	*/
	BIA_EXPORT static bool parse_sign(stream::buffer_input_stream::buffer_type & _buffer, encoding::encoder * _encoder);
	BIA_EXPORT static int match_native_number(stream::buffer_input_stream::buffer_type & _buffer, encoding::encoder * _encoder, int _base, bool _negative, token_output & _output);
	BIA_EXPORT static int parse_base(stream::buffer_input_stream::buffer_type & _buffer, encoding::encoder * _encoder);
	/*
	 * Matches single- and multiline comments and @a _is_ws.
	 *
	 * @since 3.68.141.794
	 * @date 2-Dec-18
	 *
	 * @param [in] _input The input buffer.
	 * @param [in] _encoder The encoder.
	 * @param _is_ws The whitespace checker.
	 * @param _end_predicate (Optional) If specified the automaton ends prematurely and returns -1. Multiline comments are not affected by this predicate.
	 *
	 * @throws See stream::buffer_input_stream::available(), stream::buffer_input_stream::buffer() and stream::buffer_input_stream::skip().
	 * @throws See encoding::encoder::next().
	 *
	 * @return 1 if the automaton matched whitespaces/comments successfully. -1 if @a _end_predicate fired, otherwise 0.
	*/
	BIA_EXPORT static int whitespace_automaton(stream::buffer_input_stream & _input, encoding::encoder * _encoder, bool(*_is_ws)(encoding::code_point), bool(*_end_predicate)(encoding::code_point) = nullptr);
};

}
}
