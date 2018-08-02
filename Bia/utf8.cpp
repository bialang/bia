#include "utf8.hpp"
#include "exception.hpp"


namespace bia
{
namespace encoding
{

void utf8::append(code_point _char, int8_t *& _begin, const int8_t * _end)
{
	// Check character
	if (_char < 0) {
		throw exception::encoding_error(BIA_EM_INVALID_UNICODE);
	}

	auto _size = _end - _begin;

	// One byte
	if (_char <= 0x7f) {
		// Check size
		if (!_size) {
			throw exception::encoding_error(BIA_EM_NOT_ENOUGH_SPACE);
		}

		*_begin = static_cast<int8_t>(_char);
		++_begin;
	} // Two bytes
	else if (_char <= 0x7ff) {
		// Check size
		if (_size < 2) {
			throw exception::encoding_error(BIA_EM_NOT_ENOUGH_SPACE);
		}

		*_begin = static_cast<int8_t>((_char >> 6 & 0x1f) | 0xc0);
		_begin[1] = static_cast<int8_t>((_char & 0x3f) | 0x80);
		_begin += 2;
	} // Three bytes
	else if (_char <= 0xffff) {
		// Reserved character
		if (is_reserved(_char)) {
			throw exception::encoding_error(BIA_EM_INVALID_UNICODE);
		} // Check size
		else if (_size < 3) {
			throw exception::encoding_error(BIA_EM_NOT_ENOUGH_SPACE);
		}

		*_begin = static_cast<int8_t>((_char >> 12 & 0xf) | 0xe0);
		_begin[1] = static_cast<int8_t>((_char >> 6 & 0x3f) | 0x80);
		_begin[2] = static_cast<int8_t>((_char & 0x3f) | 0x80);
		_begin += 3;
	} // Four bytes
	else if (_char <= 0x10ffff) {
		// Reserved character
		if (is_reserved(_char)) {
			throw exception::encoding_error(BIA_EM_INVALID_UNICODE);
		} // Check size
		else if (_size < 4) {
			throw exception::encoding_error(BIA_EM_NOT_ENOUGH_SPACE);
		}

		*_begin = static_cast<int8_t>((_char >> 18 & 0x7) | 0xf0);
		_begin[1] = static_cast<int8_t>((_char >> 12 & 0x3f) | 0x80);
		_begin[2] = static_cast<int8_t>((_char >> 6 & 0x3f) | 0x80);
		_begin[3] = static_cast<int8_t>((_char & 0x3f) | 0x80);
		_begin += 4;
	} // Out of unicode range
	else {
		throw exception::encoding_error(BIA_EM_INVALID_UNICODE);
	}
}

bool utf8::has_next(const int8_t * _begin, const int8_t * _end) noexcept
{
	try {
		auto _tmp = _begin;
		
		next(_tmp, _end);

		return true;
	} catch (...) {
		return false;
	}
}

code_point utf8::next(const int8_t *& _begin, const int8_t * _end)
{
	code_point _char = 0;
	auto _size = _end - _begin;

	// End of string
	if (_size <= 0) {
		return 0;
	}

	// One byte
	if (!(*_begin & 0x80)) {
		_char = *_begin & 0x7f;
		++_begin;
	} // Two bytes
	else if ((*_begin & 0xe0) == 0xc0) {
		// Check size
		if (_size < 2) {
			throw exception::encoding_error(BIA_EM_NOT_ENOUGH_SPACE);
		}

		_char = (*_begin & 0x1f) << 6 | (_begin[1] & 0x3f);

		// Check char
		if (_char < 0x80) {
			throw exception::encoding_error(BIA_EM_INVALID_ENCODING);
		}

		_begin += 2;
	} // Three bytes
	else if ((*_begin & 0xf0) == 0xe0) {
		// Check size
		if (_size < 3) {
			throw exception::encoding_error(BIA_EM_NOT_ENOUGH_SPACE);
		}

		_char = (*_begin & 0x0f) << 12 | (_begin[1] & 0x3f) << 6 | (_begin[2] & 0x3f);

		// Check char
		if (_char < 0x800) {
			throw exception::encoding_error(BIA_EM_INVALID_ENCODING);
		} // Reserved character
		else if (is_reserved(_char)) {
			throw exception::encoding_error(BIA_EM_INVALID_UNICODE);
		}

		_begin += 3;
	} // Four bytes
	else if ((*_begin & 0xf8) == 0xf0) {
		// Check size
		if (_size < 4) {
			throw exception::encoding_error(BIA_EM_NOT_ENOUGH_SPACE);
		}

		_char = (*_begin & 0x07) << 18 | (_begin[1] & 0x3f) << 12 | (_begin[2] & 0x3f) << 6 | (_begin[3] & 0x3f);

		// Check char
		if (_char < 0x10000) {
			throw exception::encoding_error(BIA_EM_INVALID_ENCODING);
		} // Reserved character
		else if (is_reserved(_char)) {
			throw exception::encoding_error(BIA_EM_INVALID_UNICODE);
		}

		_begin += 4;
	} // Invalid
	else {
		throw exception::encoding_error(BIA_EM_INVALID_ENCODING);
	}

	return _char;
}

}
}