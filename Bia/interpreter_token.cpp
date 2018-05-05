#include "interpreter_token.hpp"

#include <cctype>


namespace bia
{
namespace grammar
{

const std::regex interpreter_token::_number_pattern(R"delim(^(-|+)?(?:0(?:b|B)([01]['01]*)|0(?:x|X)([0-9a-fA-F]['0-9a-fA-F]*)|0([0-7]['0-7]*)|(\d['0-9]*(\.)?(?:\d['0-9]*)?)(f|F)?))delim");

ACTION interpreter_token::number(stream::input_stream & _input, token_param _params, token_output & _output) noexcept
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	std::cmatch _results;

	// No input
	if (_input.available() <= 0) {
		return error;
	}

	auto _buffer = _input.get_buffer();

	if (std::regex_search(reinterpret_cast<const char*>(_buffer.first), reinterpret_cast<const char*>(_buffer.second), _results, _number_pattern)) {
		// Sign
		auto _group = _results[1];
		auto _negative = false;

		if (_group.length() && _group.first[0] == '-') {
			_negative = true;
		}

		// Integer
		_output.content.type = report::TYPE::INT_VALUE;

		// Decimal base
		_group = _results[5];

		if (_group.length()) {
			// Floating point
			if (_results[6].length() || _results[7].length()) {
				_output.content.type = report::TYPE::FLOAT_VALUE;
				_output.content.content.floatValue = parse_double(_buffer, _params.encoder) * (_negative ? -1 : 1);
			} else {
				_output.content.content.intValue = parse_integer(_buffer, _params.encoder, 10) * (_negative ? -1 : 1);
			}

			goto gt_success;
		}

		// Hex base
		_group = _results[2];

		if (_group.length()) {
			_output.content.content.intValue = parse_integer(_buffer, _params.encoder, 16) * (_negative ? -1 : 1);

			goto gt_success;
		}

		// Binary base
		_group = _results[3];

		if (_group.length()) {
			_output.content.content.intValue = parse_integer(_buffer, _params.encoder, 2) * (_negative ? -1 : 1);

			goto gt_success;
		}

		// Octal base
		_group = _results[4];

		if (_group.length()) {
			_output.content.content.intValue = parse_integer(_buffer, _params.encoder, 8) * (_negative ? -1 : 1);

			goto gt_success;
		}

		// Success
		if (false) {
		gt_success:;

			_input.skip(_results.length());

			return success;
		}
	}

	return error;
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
	_output.content.content.member = _params.context->get_address(utility::string_key(reinterpret_cast<const char*>(_begin), reinterpret_cast<const char*>(_buffer.first)));

	// Move cursor
	_input.skip(_buffer.first);

	return success;
}

ACTION interpreter_token::assign_operator(stream::input_stream & _input, token_param _params, token_output & _output)
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	// Optional starting whitespaces

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
			case '#':
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