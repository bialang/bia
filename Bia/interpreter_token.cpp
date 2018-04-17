#include "interpreter_token.hpp"

#include <cctype>


namespace bia
{
namespace grammar
{

const std::regex interpreter_token::_number_pattern(R"delim(^(-|+)?(?:(\d['0-9]+\.(?:\d['0-9]*)?)(f|F)?|(?:0b([01]['01]*))|(?:0x([0-9a-fA-F]['0-9a-fA-F]*))|(?:0([0-7]['0-7]*))|(\d['0-9]*)))delim");


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

ACTION interpreter_token::comment(stream::input_stream & _input, token_param _params, token_output & _output) noexcept
{
	constexpr auto success = ACTION::DONT_REPORT;
	constexpr auto error = ACTION::ERROR;

	// Check if this is a comment
	auto _buffer = _input.get_buffer();
	stream::input_stream::cursor_type _read = 0;

	if (_buffer.second >= 1 && *_buffer.first == '#') {
		++_read;

		// Ignore every character until a line break
		while (true) {
			if (_read == _buffer.second) {
				// There is still more
				if (_input.has_next()) {
					_input.skip(_read);

					_buffer = _input.get_buffer();
					_read = 0;
				}
			}
		}
	}

	if (_length >= 1 && *_buffer++ == '#') {
		++_output.length;

		// Ignore every character until a line break
		while (--_length) {
			++_output.length;

			if (*_buffer++ == '\n') {
				break;
			}
		}

		return success;
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

}
}