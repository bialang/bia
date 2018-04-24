#include "interpreter_token.hpp"

#include <cctype>


namespace bia
{
namespace grammar
{

const std::regex interpreter_token::_number_pattern(R"delim(^(-|+)?(?:(\d['0-9]+\.(?:\d['0-9]*)?)(f|F)?|(?:0(?:b|B)([01]['01]*))|(?:0(?:x|X)([0-9a-fA-F]['0-9a-fA-F]*))|(?:0([0-7]['0-7]*))|(\d['0-9]*)))delim");

ACTION interpreter_token::number(stream::input_stream & _input, token_param _params, token_output & _output) noexcept
{
	constexpr auto success = ACTION::REPORT;
	constexpr auto error = ACTION::ERROR;

	std::cmatch _results;

	if (std::regex_search(_buffer, _buffer + _length, _results, _number_pattern)) {
		// Sign
		auto _group = _results[1];

		if (_group.length() && _group.first[0] == '-') {
			_output.custom |= grammar::NI_NEGATIVE_NUMBER;
		}

		// Float or double
		_group = _results[2];

		if (_group.length()) {
			// Float
			if (_results[2].length()) {
				_output.content.type = report::TYPE::FLOAT_VALUE;
				_output.content.content.floatValue = parse_floating_point<float>(nullptr, 0, _output.custom);
			} // Double
			else {
				_output.content.type = report::TYPE::DOUBLE_VALUE;
				_output.content.content.doubleValue = parse_floating_point<double>(nullptr, 0, _output.custom);
			}

			_output.length = _group.length();
			_output.custom |= (_output.padding = _results[2].length()) ? grammar::NI_FLOAT : grammar::NI_DOUBLE;

			return success;
		}

		// Integer
		_output.custom |= grammar::NI_INTEGER;

		// Decimal base
		_group = _results[7];

		if (_group.length()) {
			_output.length = _group.length();
			_output.custom |= 10;

			return success;
		}

		// Hex base
		_group = _results[5];

		if (_group.length()) {
			_output.length = _group.length();
			_output.custom |= 16;

			return success;
		}

		// Binary base
		_group = _results[4];

		if (_group.length()) {
			_output.length = _group.length();
			_output.custom |= 2;

			return success;
		}

		// Octal base
		_group = _results[6];

		if (_group.length()) {
			_output.length = _group.length();
			_output.custom |= 8;

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
	if (*_buffer.first != '_' && !std::isalpha(*_buffer.first)) {
		return error;
	}

	int _length = 1;

	++_buffer.first;

	// Rest
	while (_buffer.first < _buffer.second) {
		if (*_buffer.first == '_' || std::isalnum(*_buffer.first)) {
			++_buffer.first;

			// Max identifier length reached
			if (++_length > BIA_MAX_IDENTIFIER_LENGTH) {
				return error;
			}
		} else {
			break;
		}
	}

	// Get address
	_output.content.content.member = _params.context->get_address(_begin);

	// Move cursor
	_input.skip(_buffer.first);

	return success;
}

ACTION interpreter_token::comment(stream::input_stream & _input, token_param _params, token_output & _output) noexcept
{
	constexpr auto success = ACTION::DONT_REPORT;
	constexpr auto error = ACTION::ERROR;

	auto _first_iter = true;

	// Check if this is a comment
	while (_input.available() > 0) {
		auto _buffer = _input.get_buffer();

		// Check for comment character
		if (_first_iter && *_buffer.first++ != '#') {
			return error;
		}

		_first_iter = false;

		// Ignore every character until a line break
		while (_buffer.first < _buffer.second) {
			if (*_buffer.first++ == '\n') {
				// Move cursor
				_input.skip(_buffer.first);

				return success;
			}
		}

		// Move cursor
		_input.skip(_buffer.first);
	}

	return error;
}

ACTION interpreter_token::command_end(const char * _buffer, size_t _length, token_param _params, token_output & _output) noexcept
{
	constexpr auto success = ACTION::DONT_REPORT;
	constexpr auto error = ACTION::ERROR;

	while (_output.length < _length) {
		switch (_buffer[_output.length++]) {
		case ' ':
		case '\t':
		case '\r':
			break;
		case '\n':
			return success;
		default:
			return error;
		}
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

int64_t interpreter_token::parse_integer(const char * _number, size_t _length, report::custom_type _custom) noexcept
{
	int64_t _result = 0;
	auto _base = _custom & grammar::NI_BASE_MASK;
	size_t i = 0;

	for (; i < _length; ++i) {
		if (_number[i] != '\'') {
			_result = _result * _base + get_value(_number[i]);
		}
	}

	// Negative
	if (_custom & grammar::NI_NEGATIVE_NUMBER) {
		return _result * -1;
	}

	return _result;
}

}
}