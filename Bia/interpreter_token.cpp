#include "interpreter_token.hpp"
#include "big_int_allocator.hpp"

#include <cctype>
#include <limits>


namespace bia
{
namespace grammar
{

bool interpreter_token::whitespace_skipper(stream::input_stream & _input, encoding::encoder * _encoder)
{
	return whitespace_automaton(_input, _encoder, [](encoding::code_point _char) {
		return _char == ' ' || _char == '\t';
	});
}

bool interpreter_token::padding_skipper(stream::input_stream & _input, encoding::encoder * _encoder)
{
	return whitespace_automaton(_input, _encoder, [](encoding::code_point _char) {
		return _char == ' ' || _char == '\t' || _char == '\n' || _char == '\r';
	});
}

ACTION interpreter_token::number(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	auto _buffer = _input.buffer();
	auto _negative = parse_sign(_buffer, _params.encoder);
	auto _base = parse_base(_buffer, _params.encoder);

	// Zero
	if (!_base) {
		_output.type = report::TYPE::INT_VALUE;
		_output.content.int_value = 0;

		_input.skip(_buffer.first);

		return success;
	} // Error
	else if (_base < 0) {
		return error;
	}

	// Match
	auto _tmp = _buffer.first;
	auto _result = match_native_number(_buffer, _params.encoder, _base, _negative, _output);

	if (!_result) {
		_input.skip(_buffer.first);

		return success;
	} else if (_result > 0) {
		_input.skip(_tmp);
	} else {
		return error;
	}

	// Big integer
	stream::string_stream _string(_params.context->allocator());

	_string.set_codec(stream::string_stream::CODEC::ASCII);

	match_big_integer(_input, _string, _params.encoder, _base);

	_string.finish();

	// Construct big integer
	auto _new_int = _params.context->big_int_allocator()->construct_big_int(stream::string_stream::string<char>(_string.buffer()), _base);

	if (_negative) {
		_new_int->negate();
	}

	_params.schein.register_big_int(_new_int);
	_output.type = report::TYPE::BIG_INT_VALUE;
	_output.content.big_int_value = _new_int;

	return success;
}

ACTION interpreter_token::string(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	enum FLAGS : uint32_t
	{
		F_SINGLE_QUOTE = 0x1,
		F_DOUBLE_QUOTE = 0x2,
		F_QUOTE_SET = F_SINGLE_QUOTE | F_DOUBLE_QUOTE,
		F_PREFIX_LOWER_U = 0x4,
		F_RAW_STRING = 0x8
	};

	uint32_t _flags = 0;
	stream::input_stream::buffer_type _buffer;
	stream::input_stream::cursor_type _delimitor = 0;
	stream::string_stream _string(_params.context->allocator());

	// Determine delimitor and quote
	while (true) {
		// No buffer available
		if (_input.available() <= 0) {
			return error;
		}

		_buffer = _input.buffer();

		while (_buffer.first < _buffer.second) {
			switch (_params.encoder->next(_buffer.first, _buffer.second)) {
			case '"':
			{
				_flags |= F_DOUBLE_QUOTE;

				// Move cursor
				_input.skip(_buffer.first);

				goto gt_break;
			}
			case '\'':
			{
				_flags |= F_SINGLE_QUOTE;

				// Move cursor
				_input.skip(_buffer.first);

				goto gt_break;
			}
			case 'u':
			{
				if (_string.codec_set() || _flags & F_PREFIX_LOWER_U) {
					return error;
				}

				_flags |= F_PREFIX_LOWER_U;

				break;
			}
			case 'U':
			{
				if (_string.codec_set() || _flags & F_PREFIX_LOWER_U) {
					return error;
				}

				_string.set_codec(stream::string_stream::CODEC::UTF32);
				_output.custom_parameter = report::UTF32;

				break;
			}
			case '8':
			{
				if (!(_flags & F_PREFIX_LOWER_U)) {
					return error;
				}

				_string.set_codec(stream::string_stream::CODEC::UTF8);
				_output.custom_parameter = report::UTF8;
				_flags &= ~F_PREFIX_LOWER_U;

				break;
			}
			default:
				return error;
			}
		}

		// Move cursor
		_input.skip(_buffer.first);
	}

gt_break:;

	// Set encoder if not happened
	if (!_string.codec_set()) {
		// Set UTF-16
		if (_flags & F_PREFIX_LOWER_U) {
			_string.set_codec(stream::string_stream::CODEC::UTF16);
			_output.custom_parameter = report::UTF16;
		} // Fall back to ASCII
		else {
			_string.set_codec(stream::string_stream::CODEC::ASCII);
			_output.custom_parameter = report::ASCII;
		}
	}

	auto _escape_next = false;

	while (_input.available() > 0) {
		_buffer = _input.buffer();

		while (_buffer.first < _buffer.second) {
			auto _code_point = _params.encoder->next(_buffer.first, _buffer.second);

			// Escape this
			if (_escape_next) {
				switch (_code_point) {
				case 'r':
					_string.append('\r');

					break;
				case 'n':
					_string.append('\n');

					break;
				case 'a':
					_string.append('\a');

					break;
				case 't':
					_string.append('\t');

					break;
				default:
					_string.append(_code_point);

					break;
				}

				_escape_next = false;
			} else {
				switch (_code_point) {
				case '\\':
				{
					if (!(_flags & F_RAW_STRING)) {
						_escape_next = true;
					} else {
						goto gt_default;
					}

					break;
				}
				case '"':
				{
					if (_flags & F_DOUBLE_QUOTE) {
						goto gt_end;
					}

					goto gt_default;
				}
				case '\'':
				{
					if (_flags & F_SINGLE_QUOTE) {
						goto gt_end;
					}
				}
				default:
				gt_default:;
					_string.append(_code_point);

					break;
				}
			}
		}
	}

gt_end:;
	_input.skip(_buffer.first);
	_string.finish();

	// Transfer ownership
	machine::memory::universal_allocation _string_buffer(std::move(_string.buffer()));

	// Register the buffer
	_output.type = report::TYPE::STRING;
	_output.content.string = _string_buffer;
	_params.context->string_manager().register_string(_string_buffer);

	return success;
}

ACTION interpreter_token::identifier(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	// No input
	if (_input.available() <= 0) {
		return error;
	}

	auto _buffer = _input.buffer();
	auto _begin = _buffer.first;

	// First character
	if (_params.encoder->has_next(_buffer.first, _buffer.second)) {
		auto _first = _params.encoder->next(_buffer.first, _buffer.second);

		if (_first != '_' && !encoding::encoder::is_alpha(_first)) {
			return error;
		}
	} else {
		return error;
	}

	int _length = _buffer.first - _begin;

	// Rest
	while (_params.encoder->has_next(_buffer.first, _buffer.second)) {
		auto _tmp = _buffer.first;
		auto _code_point = _params.encoder->next(_buffer.first, _buffer.second);

		if (_code_point == '_' || encoding::encoder::is_alnum(_code_point)) {
			// Max identifier length reached
			_length += _buffer.first - _tmp;

			if (_length > BIA_MAX_IDENTIFIER_LENGTH) {
				return error;
			}
		} else {
			_buffer.first = _tmp;

			break;
		}
	}

	// Get address
	_output.type = report::TYPE::MEMBER;
	_output.content.member = _params.context->name_address(utility::string_key(reinterpret_cast<const char*>(_begin), _length));

	// Move cursor
	_input.skip(_buffer.first);

	return success;
}

ACTION interpreter_token::first_member(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;
	auto _mark = _input.mark();

	// Starting optional whitespaces
	if (!whitespace_deleter<flags::starting_ws_opt_token, true>(_input, _params.encoder)) {
		return error;
	}

	// First element
	if (string(_input, _params, _output) != ACTION::REPORT) {
		report::custom_type _info = 0;
		_output = {};

		_input.reset(_mark);

		if (keyword<keyword_copyof, flags::ending_ws_token>(_input, _params, _output) == ACTION::REPORT) {
			_info = keyword_copyof::string_id();
		} else if (keyword<keyword_refof, flags::ending_ws_token>(_input, _params, _output) == ACTION::REPORT) {
			_info = keyword_refof::string_id();
		} else {
			_input.reset(_mark);
		}

		// Try identifier
		if (identifier(_input, _params, _output) != ACTION::REPORT) {
			return error;
		}

		_output.custom_parameter = _info;
	}

	return success;
}

ACTION interpreter_token::control_statement(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;
	
	if (keyword<keyword_break>(_input, _params, _output) != success && 
		keyword<keyword_continue>(_input, _params, _output) != success &&
		keyword<keyword_goto>(_input, _params, _output) != success &&
		keyword<keyword_exit_scope>(_input, _params, _output) != success &&
		keyword<keyword_delete>(_input, _params, _output) != success) {
		return error;
	}

	// Additional identifier
	if (_output.content.keyword == keyword_goto::string_id()) {
		identifier(_input, _params, _output);

		return error;
	}

	_output.rule_id = BGR_CONTROL_STATEMENT;

	// Match end
	return command_end(_input, _params, _output) == ACTION::DONT_REPORT ? success : error;
}

ACTION interpreter_token::assign_operator(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	// Starting optional whitespaces
	if (!whitespace_deleter<flags::starting_ws_opt_token, true>(_input, _params.encoder)) {
		return error;
	}

	if (_input.available() > 0) {
		auto _max = BIA_MAX_OPERATOR_LENGTH;
		auto _buffer = _input.buffer();

		while (_max-- && _params.encoder->has_next(_buffer.first, _buffer.second)) {
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
			case '=':
			{
				_output.content.operator_code = _output.content.operator_code << 8 | '=';
				_output.type = report::TYPE::OPERATOR_CODE;

				// Move cursor
				_input.skip(_buffer.first);

				return success;
			}
			default:
				return error;
			}
		}
	}

	return error;
}

ACTION interpreter_token::compare_operator(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	// Starting optional whitespaces
	if (!whitespace_deleter<flags::starting_ws_opt_token, true>(_input, _params.encoder)) {
		return error;
	}

	auto _buffer = _input.buffer();
	auto _optional = false;

	_output.type = report::TYPE::OPERATOR_CODE;
	_output.content.operator_code = _params.encoder->next(_buffer.first, _buffer.second);

	switch (_output.content.operator_code) {
	case '<':
	case '>':
		_optional = true;
	case '=':
	case '!':
	{
		// Need at least one more
		auto _prev = _buffer.first;

		if (_params.encoder->next(_buffer.first, _buffer.second) != '=') {
			if (_optional) {
				// Move cursor
				_input.skip(_prev);

				return success;
			} else {
				return error;
			}
		}

		_output.content.operator_code = _output.content.operator_code << 8 | '=';

		if (!_optional) {
			// Can be the same operator
			_prev = _buffer.first;

			if (_params.encoder->next(_buffer.first, _buffer.second) == '=') {
				_output.content.operator_code = _output.content.operator_code << 8 | '=';
			} else {
				_buffer.first = _prev;
			}
		}

		// Move cursor
		_input.skip(_buffer.first);

		return success;
	}
	default:
		break;
	}

	return error;
}

ACTION interpreter_token::dot_operator(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	// Starting optional whitespaces
	if (!whitespace_deleter<flags::starting_ws_opt_token, true>(_input, _params.encoder)) {
		return error;
	}

	auto _buffer = _input.buffer();

	_output.type = report::TYPE::OPERATOR_CODE;

	switch (_params.encoder->next(_buffer.first, _buffer.second)) {
	case '*':
	{
		// Double times
		auto _prev = _buffer.first;

		if (_params.encoder->next(_buffer.first, _buffer.second) == '*') {
			_output.content.operator_code = '*' << 8 | '*';
		} else {
			_output.content.operator_code = '*';
			_buffer.first = _prev;
		}

		break;
	}
	case '/':
	{
		// Double divide
		auto _prev = _buffer.first;

		if (_params.encoder->next(_buffer.first, _buffer.second) == '/') {
			_output.content.operator_code = '/' << 8 | '/';
		} else {
			_output.content.operator_code = '/';
			_buffer.first = _prev;
		}

		break;
	}
	case '%':
		_output.content.operator_code = '%';

		break;
	default:
		return error;
	}

	// Move
	_input.skip(_buffer.first);

	return success;
}

ACTION interpreter_token::command_end(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::DONT_REPORT;
	constexpr auto error = ACTION::ERROR;

	return whitespace_automaton(_input, _params.encoder, [](encoding::code_point _char) {
		return _char == ' ' || _char == '\t';
	}, [](encoding::code_point _char) {
		return _char == '\n' || _char == ';';
	}) == -1 || _input.available() == 0 ? success : error;
}

void interpreter_token::match_big_integer(stream::input_stream & _input, stream::string_stream & _output, encoding::encoder * _encoder, int _base)
{
	while (_input.available() > 0) {
		auto _buffer = _input.buffer();
		auto _last_digit = _buffer.first;

		while (_buffer.first < _buffer.second) {
			auto _digit = _encoder->next(_buffer.first, _buffer.second);

			// Skip ' and _
			if (_digit == '\'' || _digit == '_') {
				if (_buffer.first >= _buffer.second) {
					break;
				}

				_digit = _encoder->next(_buffer.first, _buffer.second);
			}

			// Valid digit
			if (encoding::encoder::hex_value(_digit) < _base) {
				_output.append(_digit);
			} else {
				_input.skip(_last_digit);

				return;
			}

			_last_digit = _buffer.first;
		}

		_input.skip(_last_digit);
	}
}

bool interpreter_token::parse_sign(stream::input_stream::buffer_type & _buffer, encoding::encoder * _encoder)
{
	auto _negative = false;

	// As long as input is available
	if (_buffer.first < _buffer.second) {
		auto _tmp = _buffer.first;

		switch (_encoder->next(_buffer.first, _buffer.second)) {
		case '-':
			_negative = true;
		case '+':
			break;
		default:
			_buffer.first = _tmp;

			break;
		}
	}

	return _negative;
}

int interpreter_token::match_native_number(stream::input_stream::buffer_type & _buffer, encoding::encoder * _encoder, int _base, bool _negative, token_output & _output)
{
	auto _last_digit = _buffer.first;
	auto _digit_matched = false;
	auto _decimal_place = false;
	auto _fraction = 1.0;

	if (_buffer.first >= _buffer.second) {
		return -1;
	}

	// First digit cannot be a seperator
	switch (_encoder->peek(_buffer.first, _buffer.second)) {
	case '\'':
	case '_':
		return -1;
	default:
		break;
	}

	_output.type = report::TYPE::INT_VALUE;
	_output.content.double_value = 0;

	while (_buffer.first < _buffer.second) {
		auto _digit = _encoder->next(_buffer.first, _buffer.second);

		// Skip ' and _
		if (_digit == '\'' || _digit == '_' || (!_decimal_place && _digit == '.')) {
			// Switch to double
			if (_digit == '.') {
				if (_output.type == report::TYPE::INT_VALUE) {
					_output.type = report::TYPE::DOUBLE_VALUE;
					_output.content.double_value = static_cast<double>(_output.content.int_value);
				}

				_last_digit = _buffer.first;
				_digit_matched = true;
				_decimal_place = true;
			}

			if (_buffer.first >= _buffer.second) {
				break;
			}

			_digit = _encoder->next(_buffer.first, _buffer.second);
		}

		auto _digit_value = encoding::encoder::hex_value(_digit);

		// Not a digit
		if (_digit_value >= _base) {
			// Not a single digit matched
			if (!_digit_matched) {
				return -1;
			}

			break;
		} else if (_negative) {
			// Number is too small
			if (_output.type == report::TYPE::INT_VALUE) {
				// Switch to double, because it still could be a native double
				if ((std::numeric_limits<int64_t>::min() + _digit_value) / _base > _output.content.int_value) {
					_output.type = report::TYPE::DOUBLE_VALUE;
					_output.content.double_value = static_cast<double>(_output.content.int_value) * _base - _digit_value;
				} // Int
				else {
					_output.content.int_value = _output.content.int_value * _base - _digit_value;
				}
			} // Double
			else {
				if (_decimal_place) {
					_output.content.double_value -= _digit_value / (_fraction *= 10);
				} else {
					// Double underflow
					if ((std::numeric_limits<double>::lowest() + _digit_value) / _base > _output.content.double_value) {
						if (_decimal_place) {
							throw exception::overflow_error(BIA_EM_DOUBLE_UNDERFLOW);
						}

						return 1;
					}

					_output.content.double_value = _output.content.double_value * _base - _digit_value;
				}
			}
		} // Int
		else if (_output.type == report::TYPE::INT_VALUE) {
			// Switch to double, because it still could be a native double
			if ((std::numeric_limits<int64_t>::max() - _digit_value) / _base < _output.content.int_value) {
				_output.type = report::TYPE::DOUBLE_VALUE;
				_output.content.double_value = static_cast<double>(_output.content.int_value) * _base + _digit_value;
			} // Int
			else {
				_output.content.int_value = _output.content.int_value * _base + _digit_value;
			}
		} // Double
		else {
			if (_decimal_place) {
				_output.content.double_value += _digit_value / (_fraction *= 10);
			} else {
				// Double underflow
				if ((std::numeric_limits<double>::max() - _digit_value) / _base < _output.content.double_value) {
					if (_decimal_place) {
						throw exception::overflow_error(BIA_EM_DOUBLE_UNDERFLOW);
					}

					return 1;
				}

				_output.content.double_value = _output.content.double_value * _base + _digit_value;
			}
		}

		_last_digit = _buffer.first;
		_digit_matched = true;
	}

	// Big integer
	if (_output.type == report::TYPE::DOUBLE_VALUE && !_decimal_place) {
		return 1;
	}

	_buffer.first = _last_digit;

	return 0;
}

int interpreter_token::parse_base(stream::input_stream::buffer_type & _buffer, encoding::encoder * _encoder)
{
	if (_buffer.first >= _buffer.second) {
		return -1;
	}

	auto _base = 10;
	auto _tmp = _buffer.first;
	auto _digit = _encoder->next(_buffer.first, _buffer.second);

	// Can be zero, hex, octal or binary
	if (_digit == '0') {
		if (_buffer.first < _buffer.second) {
			_tmp = _buffer.first;
			_digit = _encoder->next(_buffer.first, _buffer.second);

			// Hex
			if (_digit == 'x' || _digit == 'X') {
				_base = 16;
			} // Binary
			else if (_digit == 'b' || _digit == 'B') {
				_base = 2;
			} // Octal
			else if (_digit >= '0' && _digit <= '7') {
				_base = 8;
				_buffer.first = _tmp;
			} // Decimal
			else if (_digit == '.') {
				_buffer.first = _tmp;
			}
			// Matched only a zero
			else {
				_buffer.first = _tmp;

				return 0;
			}
		} // Is zero
		else {
			return 0;
		}
	} // Decimal
	else if (_digit >= '1' && _digit <= '9') {
		_buffer.first = _tmp;

		return 10;
	} // Error
	else {
		return -1;
	}

	return _base;
}

int interpreter_token::whitespace_automaton(stream::input_stream & _input, encoding::encoder * _encoder, bool(*_is_ws)(encoding::code_point), bool(*_end_predicate)(encoding::code_point))
{
	enum class STATE
	{
		START,
		END,
		COMMENT_START,
		COMMENT_SINGLE_LINE,
		COMMENT_MULTILINE_CONTENT,
		COMMENT_MULTILINE_END,
	};

	STATE _state = STATE::START;
	stream::input_stream::buffer_type::first_type _skipped = nullptr;

	while (_input.available() > 0) {
		auto _buffer = _input.buffer();
		stream::input_stream::buffer_type::first_type _tmp = nullptr;

		_skipped = nullptr;

		while (_buffer.first < _buffer.second) {
			auto _char = _encoder->next(_buffer.first, _buffer.second);

			// End predicate only if not in multiline comment
			if (_state != STATE::COMMENT_MULTILINE_CONTENT && _state != STATE::COMMENT_MULTILINE_END && _end_predicate && _end_predicate(_char)) {
				_input.skip(_buffer.first);

				return -1;
			}

			switch (_state) {
			case STATE::START:
			{
				if (_is_ws(_char)) {
					_state = STATE::END;
				} else if (_char == '#') {
					_state = STATE::COMMENT_START;
				} else {
					goto gt_loop_break;
				}

				break;
			}
			case STATE::END:
			{
				_skipped = _tmp;

				if (_char == '#') {
					_state = STATE::COMMENT_START;
				} else if (!_is_ws(_char)) {
					goto gt_loop_break;
				}

				break;
			}
			case STATE::COMMENT_START:
			{
				if (_char == '>') {
					_state = STATE::COMMENT_MULTILINE_CONTENT;
				} else if (_char == '#' || _char == '\n') {
					_state = STATE::END;
				} else {
					_state = STATE::COMMENT_SINGLE_LINE;
				}

				break;
			}
			case STATE::COMMENT_SINGLE_LINE:
			{
				if (_char == '\n' || _char == '#') {
					_state = STATE::END;
				}

				break;
			}
			case STATE::COMMENT_MULTILINE_CONTENT:
			{
				if (_char == '<') {
					_state = STATE::COMMENT_MULTILINE_END;
				}

				break;
			}
			case STATE::COMMENT_MULTILINE_END:
			{
				if (_char == '#') {
					_skipped = _buffer.first;
					_state = STATE::END;
				} else if (_char != '<') {
					_state = STATE::COMMENT_MULTILINE_CONTENT;
				}

				break;
			}
			}

			_tmp = _buffer.first;
		}

		// Cleanup and terminate
		if (false) {
		gt_loop_break:;
			if (_skipped) {
				_input.skip(_skipped);
			}

			break;
		}

		_input.skip(_buffer.first);
	}

	return _skipped || _state == STATE::END ? 1 : 0;
}

}
}
