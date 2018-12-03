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
	auto _skipped = false;

	while (_input.available() > 0) {
		auto _buffer = _input.buffer();

		// Has no next
		if (!_encoder->has_next(_buffer.first, _buffer.second)) {
			break;
		}

		// Ignore every character until a line break
		do {
			auto _prev = _buffer.first;

			switch (_encoder->next(_buffer.first, _buffer.second)) {
			case ' ':
			case '\t':
			case '\r':
				_skipped = true;

				break;
			default:
				_input.skip(_prev);

				return _skipped;
			}
		} while (_encoder->has_next(_buffer.first, _buffer.second));

		// Move cursor
		_input.skip(_buffer.first);
	}

	return _skipped;
}

bool interpreter_token::padding_skipper(stream::input_stream & _input, encoding::encoder * _encoder)
{
	auto _skipped = false;

	while (_input.available() > 0) {
		auto _buffer = _input.buffer();

		// Has no next
		if (!_encoder->has_next(_buffer.first, _buffer.second)) {
			break;
		}

		// Ignore every character until a line break
		do {
			auto _prev = _buffer.first;

			switch (_encoder->next(_buffer.first, _buffer.second)) {
			case ' ':
			case '\t':
			case '\r':
			case '\n':
				_skipped = true;

				break;
			default:
				_input.skip(_prev);

				return _skipped;
			}
		} while (_encoder->has_next(_buffer.first, _buffer.second));

		// Move cursor
		_input.skip(_buffer.first);
	}

	return _skipped;
}

ACTION interpreter_token::number(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	auto _negative = parse_sign(_input, _params.encoder);
	auto _base = parse_base(_input, _params.encoder);

	// Zero
	if (!_base) {
		_output.type = report::TYPE::INT_VALUE;
		_output.content.int_value = 0;

		return success;
	}

	// Match
	auto _buffer = _input.buffer();
	auto _native_match = match_native_integer(_buffer, _params.encoder, _base, _negative);

	if (std::get<0>(_native_match)) {
		_output.type = report::TYPE::INT_VALUE;
		_output.content.int_value = std::get<1>(_native_match);

		_input.skip(_buffer.first);

		return success;
	} // Error
	else if (std::get<1>(_native_match)) {
		return error;
	}

	// Big integer
	stream::string_stream _string(_params.context->allocator());

	_string.set_codec(stream::string_stream::CODEC::ASCII);

	match_big_integer(_input, _string, _params.encoder, _base);
	
	_string.finish();

	// Construct big integer
	//auto _new_int = _params.context->big_int_allocator()->construct_big_int();

	//_params.schein.register_allocation(_new_int);
	//_output.type = report::TYPE::BIG_INT_VALUE;
	//_output.content.big_int_value = _new_int;

	//mpz_set_str(_new_int, stream::string_stream::string<char>(_string.buffer()), _base);

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
		_output.content.operator_code = '*';

		break;
	default:
		return error;
	}

	// Move
	_input.skip(_buffer.first);

	return success;
}

ACTION interpreter_token::comment(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::DONT_REPORT;
	constexpr auto error = ACTION::ERROR;

	auto _first_iter = true;

	// Check if this is a comment
	while (_input.available() > 0) {
		auto _buffer = _input.buffer();

		// Has no next character
		if (!_params.encoder->has_next(_buffer.first, _buffer.second)) {
			break;
		}

		// Check for comment character
		if (_first_iter) {
			if (_params.encoder->next(_buffer.first, _buffer.second) != '#') {
				return error;
			}

			_first_iter = false;
		}

		// Ignore every character until a line break
		while (_params.encoder->has_next(_buffer.first, _buffer.second)) {
			if (_params.encoder->next(_buffer.first, _buffer.second) == '\n') {
				// Move cursor
				_input.skip(_buffer.first);

				return success;
			}
		}

		// Move cursor
		_input.skip(_buffer.first);
	}

	return _first_iter ? success : error;
}

ACTION interpreter_token::command_end(stream::input_stream & _input, token_param & _params, token_output & _output)
{
	constexpr auto success = ACTION::DONT_REPORT;
	constexpr auto error = ACTION::ERROR;

	while (_input.available() > 0) {
		auto _buffer = _input.buffer();

		if (!_params.encoder->has_next(_buffer.first, _buffer.second)) {
			break;
		}

		do {
			switch (_params.encoder->next(_buffer.first, _buffer.second)) {
			case ' ':
			case '\t':
			case '\r':
				break;
			case '\n':
			case ';':
			case 0:
				// Move cursor
				_input.skip(_buffer.first);

				return success;
			default:
				return error;
			}
		} while (_params.encoder->has_next(_buffer.first, _buffer.second));

		// Move cursor
		_input.skip(_buffer.first);
	}

	return success;
}

bool interpreter_token::parse_sign(stream::input_stream & _input, encoding::encoder * _encoder)
{
	auto _negative = false;

	// As long as input is available
	while (_input.available() > 0) {
		auto _buffer = _input.buffer();

		while (_buffer.first < _buffer.second) {
			auto _tmp = _buffer.first;

			switch (_encoder->next(_buffer.first, _buffer.second)) {
			case '-':
				_negative = !_negative;
			case '+':
				break;
			default:
				_input.skip(_tmp);

				return _negative;
			}
		}

		_input.skip(_buffer.first);
	}

	return _negative;
}

int interpreter_token::parse_base(stream::input_stream & _input, encoding::encoder * _encoder)
{
	auto _base = 10;
	auto _buffer = _input.buffer();
	auto _digit = _encoder->next(_buffer.first, _buffer.second);

	// Can be zero, hex, octal or binary
	if (_digit == '0') {
		if (_buffer.first < _buffer.second) {
			auto _prev = _buffer.first;
			
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
				_buffer.first = _prev;
			} else {
				_buffer.first = _prev;

				goto gt_zero;
			}
		} // Is zero
		else {
		gt_zero:;
			_input.skip(_buffer.first);

			return 0;
		}
	} // Decimal
	else if (_digit >= '1' && _digit <= '9') {
		return 10;
	} // Error
	else {
		return -1;
	}
	
	///TODO Remove possible leading zeros
	_input.skip(_buffer.first);

	return _base;
}

std::tuple<bool, int64_t> interpreter_token::match_native_integer(stream::input_stream::buffer_type & _buffer, encoding::encoder * _encoder, int _base, bool _negative)
{
	int64_t _value = 0;
	auto _last_digit = _buffer.first;
	auto _digit_matched = false;

	if (_buffer.first >= _buffer.second) {
		return { false, -1 };
	}

	// First digit cannot be a seperator
	switch (_encoder->peek(_buffer.first, _buffer.second)) {
	case '\'':
	case '_':
		return { false, -1 };
	default:
		break;
	}

	while (_buffer.first < _buffer.second) {
		auto _digit = _encoder->next(_buffer.first, _buffer.second);

		// Skip ' and _
		if (_digit == '\'' || _digit == '_') {
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
				return { false, -1 };
			}

			break;
		} else if (_negative) {
			// Number is too small
			if ((std::numeric_limits<int64_t>::min() + _digit_value) / _base > _value) {
				return { false, 0 };
			}

			_value = _value * _base - _digit_value;
		} else {
			// Number is too large
			if ((std::numeric_limits<int64_t>::max() - _digit_value) / _base < _value) {
				return { false, 0 };
			}

			_value = _value * _base + _digit_value;
		}

		_last_digit = _buffer.first;
		_digit_matched = true;
	}

	_buffer.first = _last_digit;

	return { true, _value };
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

std::pair<bool, int64_t> interpreter_token::match_base(stream::input_stream::buffer_type & _buffer, encoding::encoder * _encoder, int _base)
{
	const auto _begin = _buffer.first;
	int64_t _result = 0;

	// No input available
	if (_buffer.first >= _buffer.second) {
		return { false, 0 };
	}

	do {
		auto _tmp = _buffer.first;
		auto _code_point = _encoder->next(_buffer.first, _buffer.second);

		if (_code_point != '\'') {
			auto _value = encoding::encoder::hex_value(_code_point);

			if (_value < _base) {
				_result = _result * _base + _value;
			} else {
				_buffer.first = _tmp;

				// Failed
				if (_tmp == _begin) {

					return { false, 0 };
				}

				break;
			}
		}
	} while (_buffer.first < _buffer.second);

	return { true, _result };
}

std::tuple<bool, int64_t, double, bool> interpreter_token::match_decimal(stream::input_stream::buffer_type & _buffer, encoding::encoder * _encoder)
{
	const auto _begin = _buffer.first;
	auto _result = std::make_tuple<bool, int64_t, double, bool>(true, 0, 0, false);

	// Parse numbers
	while (_buffer.first < _buffer.second) {
		auto _tmp = _buffer.first;
		auto _code_point = _encoder->next(_buffer.first, _buffer.second);

		// Is floating point
		if (_code_point == '.') {
			std::get<3>(_result) = true;
			std::get<2>(_result) = static_cast<double>(std::get<1>(_result));

			goto gt_after_dot;
		} else if (_code_point != '\'') {
			// Floating point
			if (_code_point == 'f' || _code_point == 'F') {
				std::get<3>(_result) = true;
				std::get<2>(_result) = static_cast<double>(std::get<1>(_result));

				return _result;
			}

			auto _value = _code_point - '0';

			// Invalid code point
			if (_value < 0 || _value > 9) {
				if (_tmp == _begin) {
					std::get<0>(_result) = false;
				}

				_buffer.first = _tmp;

				return _result;
			}

			std::get<1>(_result) = std::get<1>(_result) * 10 + _value;
		}
	}

	// Only for floating point after the point
	if (false) {
	gt_after_dot:;
		auto _factor = 1.;

		while (_buffer.first < _buffer.second) {
			auto _tmp = _buffer.first;
			auto _code_point = _encoder->next(_buffer.first, _buffer.second);

			if (_code_point != '\'') {
				// Floating point end
				if (_code_point == 'f' || _code_point == 'F') {
					break;
				}

				auto _value = _code_point - '0';

				// Invalid code point
				if (_value < 0 || _value > 9) {
					_buffer.first = _tmp;

					return _result;
				}

				_factor /= 10.;
				std::get<2>(_result) = std::get<2>(_result) + _value * _factor;
			}
		}
	}

	return _result;
}

}
}