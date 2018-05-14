#include "interpreter_token.hpp"

#include <cctype>


namespace bia
{
namespace grammar
{

bool interpreter_token::whitespace_skipper(stream::input_stream & _input, encoding::utf * _encoder)
{
	auto _skipped = false;

	while (_input.available() > 0) {
		auto _buffer = _input.get_buffer();

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

bool interpreter_token::padding_skipper(stream::input_stream & _input, encoding::utf * _encoder)
{
	auto _skipped = false;

	while (_input.available() > 0) {
		auto _buffer = _input.get_buffer();

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

ACTION interpreter_token::number(stream::input_stream & _input, token_param _params, token_output & _output) noexcept
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	// No input
	if (_input.available() <= 0) {
		return error;
	}

	auto _buffer = _input.get_buffer();
	int64_t _int = 0;
	auto _double = 0.;
	auto _negative = false;
	auto _is_double = false;
	auto _digit = _params.encoder->next(_buffer.first, _buffer.second);

	// Optional sign
	switch (_digit) {
	case '-':
		_negative = true;
	case '+':
	{
		// No more input
		if (_buffer.first >= _buffer.second) {
			return error;
		}

		_digit = _params.encoder->next(_buffer.first, _buffer.second);
	}
	default:
		break;
	}

	// First character
	switch (_digit) {
	case '0':
	{
		// Could be other base
		if (_buffer.first < _buffer.second) {
			auto _tmp = _buffer.first;

			_digit = _params.encoder->next(_buffer.first, _buffer.second);

			int _base;

			switch (_digit) {
			case 'b':
			case 'B':
				_base = 2;

				break;
			case 'x':
			case 'X':
				_base = 16;

				break;
			case 'f':
			case 'F':
				_is_double = true;

				goto gt_set_value;
			case '.':
				_buffer.first = _tmp;

				goto gt_match_decimal;
			default:
				_buffer.first = _tmp;
				_base = 8;

				break;
			}

			// Match
			auto _result = match_base(_buffer, _params.encoder, _base);

			if (!_result.first) {
				// Result is 0
				if (_base == 8) {
					_int = 0;
					_buffer.first = _tmp;

					goto gt_set_value;
				}

				return error;
			}

			_int = _result.second;
		}

		break;
	}
	default:
	{
	gt_match_decimal:;
		bool _success;

		std::tie(_success, _int, _double, _is_double) = match_decimal(_buffer, _params.encoder);

		if (!_success) {
			return error;
		}

		break;
	}
	}

gt_set_value:;
	// Set value
	if (_is_double) {
		_output.content.type = report::TYPE::DOUBLE_VALUE;
		_output.content.content.doubleValue = _negative ? -_double : _double;
	} else {
		_output.content.type = report::TYPE::INT_VALUE;
		_output.content.content.intValue = _negative ? -_int : _int;
	}

	// Move input cursor
	_input.skip(_buffer.first);

	return success;
}

ACTION interpreter_token::string(stream::input_stream & _input, token_param _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	enum FLAGS : uint32_t
	{
		F_SINGLE_QUOTE = 0x1,
		F_QUOTE_SET = 0x2,
		F_RAW_STRING = 0x4,
		F_BINARY = 0x8,
	};

	uint32_t _flags = 0;
	stream::input_stream::buffer_type _buffer;
	stream::input_stream::cursor_type _delimitor = 0;

	// Determine delimitor and quote
	while (true) {
		// No buffer available
		if (_input.available() <= 0) {
			return error;
		}

		_buffer = _input.get_buffer();

		while (_buffer.first < _buffer.second) {
			switch (*_buffer.first++) {
			case 'R':
			{
				// Add 'R' to raw string delimitor
				if (_flags & F_QUOTE_SET) {
					++_delimitor;
				} // Start of raw string
				else if (!(_flags & F_RAW_STRING)) {
					_flags |= F_RAW_STRING;
				} else {
					return error;
				}

				break;
			}
			case '"':
			{
				// No quote has been set
				if (!(_flags & F_QUOTE_SET)) {
					_flags |= F_QUOTE_SET;

					// Read string now
					if (!(_flags & F_RAW_STRING)) {
						goto gt_break;
					}

					// Read delimitor of raw string now
				} // Add to delimiter
				else {
					++_delimitor;
				}

				break;
			}
			case '\'':
			{
				// No quote has been set
				if (!(_flags & F_QUOTE_SET)) {
					_flags |= F_QUOTE_SET | F_SINGLE_QUOTE;

					// Read string now
					if (!(_flags & F_RAW_STRING)) {
						goto gt_break;
					}

					// Read delimitor of raw string now
				} //Add to delimitor
				else {
					++_delimitor;
				}

				break;
			}
			case '(':
			{
				// Terminate delimitor of raw string
				if (_flags & F_QUOTE_SET) {
					goto gt_break;
				}

				return error;
			}
			default:
			{
				// No raw string delimitor
				if (!(_flags & F_QUOTE_SET)) {
					return error;
				}

				++_delimitor;

				break;
			}
			}
		}

		// Move cursor
		_input.skip(_buffer.first);
	}

gt_break:;

	// Raw string
	if (_flags & F_RAW_STRING) {
		while (true) {
			while (_buffer.first < _buffer.second) {
				switch (*_buffer.first++) {
				case ')':
				{
					// Compare delimitors
					if (true) {

					}
				}
				default:
					break;
				}
			}

			// Move buffer
			_input.skip(_buffer.first);

			// No buffer available
			if (_input.available() <= 0) {
				return error;
			}

			_buffer = _input.get_buffer();
		}
	} // Normal string


	return error;
}

ACTION interpreter_token::identifier(stream::input_stream & _input, token_param _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	// No input
	if (_input.available() <= 0) {
		return error;
	}

	auto _buffer = _input.get_buffer();
	auto _begin = _buffer.first;

	// First character
	if (_params.encoder->has_next(_buffer.first, _buffer.second)) {
		auto _first = _params.encoder->next(_buffer.first, _buffer.second);

		if (_first != '_' && !encoding::utf::is_alpha(_first)) {
			return error;
		}
	} else {
		return error;
	}

	int _length = 1;

	// Rest
	while (_params.encoder->has_next(_buffer.first, _buffer.second)) {
		auto _code_point = _params.encoder->next(_buffer.first, _buffer.second);

		if (_code_point == '_' || encoding::utf::is_alnum(_code_point)) {
			// Max identifier length reached
			if (++_length > BIA_MAX_IDENTIFIER_LENGTH) {
				return error;
			}
		} else {
			break;
		}
	}

	// Get address
	_output.content.content.member = _params.context->get_address_or_create(utility::string_key(reinterpret_cast<const char*>(_begin), _length));

	// Move cursor
	_input.skip(_buffer.first);

	return success;
}

ACTION interpreter_token::assign_operator(stream::input_stream & _input, token_param _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	// Starting optional whitespaces
	if (!whitespace_deleter<flags::starting_ws_opt_token, true>(_input, _params.encoder)) {
		return error;
	}

	if (_input.available() > 0) {
		auto _max = BIA_MAX_OPERATOR_LENGTH;
		auto _buffer = _input.get_buffer();

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
				_output.content.content.operatorCode = _output.content.content.operatorCode << 8 | _code_point;

				break;
			case '=':
			{
				_output.content.content.operatorCode = _output.content.content.operatorCode << 8 | '=';
				_output.content.type = report::TYPE::OPERATOR_CODE;

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

ACTION interpreter_token::compare_operator(stream::input_stream & _input, token_param _params, token_output & _output)
{
	constexpr auto success = ACTION::DONT_REPORT;
	constexpr auto error = ACTION::ERROR;

	// Starting optional whitespaces
	if (!whitespace_deleter<flags::starting_ws_opt_token, true>(_input, _params.encoder)) {
		return error;
	}

	if (_input.available() > 0) {
		auto _max = 2;
		auto _buffer = _input.get_buffer();
		int _flags = 0;
		encoding::utf::code_point _first_point = 0;

		enum FLAGS
		{
			F_REQUIRED_EQUALS = 0x1,
			F_OPTIONAL = 0x2
		};

		_output.content.type = report::TYPE::OPERATOR_CODE;

		while (_max-- && _params.encoder->has_next(_buffer.first, _buffer.second)) {
			auto _prev = _buffer.first;
			auto _code_point = _params.encoder->next(_buffer.first, _buffer.second);

			if (_max == 1) {
				_first_point = _code_point;
			}

			switch (_code_point) {
			case '=':
				if (_flags & F_REQUIRED_EQUALS) {
					_output.content.content.operatorCode = _first_point << 8 | '=';

					// Move cursor
					_input.skip(_buffer.first);

					return success;
				}
			case '!':
			{
				if (_flags & F_REQUIRED_EQUALS) {
					return error;
				}

				_flags = F_REQUIRED_EQUALS;

				break;
			}
			case '<':
			case '>':
			{
				if (_flags & F_REQUIRED_EQUALS) {
					return error;
				}

				_flags = F_REQUIRED_EQUALS | F_OPTIONAL;

				break;
			}
			default:
			{
				// Matched '<' or '>'
				if (_flags == (F_REQUIRED_EQUALS | F_OPTIONAL)) {
					_output.content.content.operatorCode = _first_point;

					// Move cursor
					_input.skip(_prev);

					return success;
				}

				return error;
			}
			}
		}
	}

	return error;
}

ACTION interpreter_token::comment(stream::input_stream & _input, token_param _params, token_output & _output) noexcept
{
	constexpr auto success = ACTION::DONT_REPORT;
	constexpr auto error = ACTION::ERROR;

	auto _first_iter = true;

	// Check if this is a comment
	while (_input.available() > 0) {
		auto _buffer = _input.get_buffer();

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

ACTION interpreter_token::command_end(stream::input_stream & _input, token_param _params, token_output & _output) noexcept
{
	constexpr auto success = ACTION::DONT_REPORT;
	constexpr auto error = ACTION::ERROR;

	while (_input.available() > 0) {
		auto _buffer = _input.get_buffer();

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

std::pair<bool, int64_t> interpreter_token::match_base(stream::input_stream::buffer_type & _buffer, encoding::utf * _encoder, int _base)
{
	return { false, 0 };
}

std::tuple<bool, int64_t, double, bool> interpreter_token::match_decimal(stream::input_stream::buffer_type & _buffer, encoding::utf * _encoder)
{
	std::tuple<bool, int64_t, double, bool> _result{};

	// Parse numbers

	std::get<0>(_result) = true;
	std::get<1>(_result) = 61;

	return _result;
}

int interpreter_token::get_value(char _digit) noexcept
{
	if (std::isdigit(_digit)) {
		return _digit - '0';
	}

	// Is hex digit
	return std::tolower(_digit) - 'a' + 10;
}

int64_t interpreter_token::parse_integer(stream::input_stream::buffer_type _buffer, encoding::utf * _encoder, int _base) noexcept
{
	int64_t _result = 0;

	while (_buffer.first < _buffer.second) {
		auto _code_point = _encoder->next(_buffer.first, _buffer.second);

		if (_code_point != '/') {
			_result = _result * _base + get_value(_code_point);
		}
	}

	return _result;
}

double interpreter_token::parse_double(stream::input_stream::buffer_type _buffer, encoding::utf * _encoder) noexcept
{
	double _result = 0.;

	// Before dot
	while (_buffer.first < _buffer.second) {
		auto _code_point = _encoder->next(_buffer.first, _buffer.second);

		if (_code_point == '.') {
			goto gt_after_dot;
		} else if (_code_point != '\'') {
			_result = _result * 10. + static_cast<double>(get_value(_code_point));
		}
	}

gt_after_dot:;
	// After dot
	auto _factor = 1.;

	while (_buffer.first < _buffer.second) {
		auto _code_point = _encoder->next(_buffer.first, _buffer.second);

		if (_code_point != '\'') {
			_factor /= 10.;
			_result = _result + static_cast<double>(get_value(_code_point)) / _factor;
		}
	}

	return _result;
}

}
}