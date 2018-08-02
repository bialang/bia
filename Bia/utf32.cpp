#include "utf32.hpp"
#include "exception.hpp"

#include <cstring>


namespace bia
{
namespace encoding
{

void utf32::append(code_point _char, int8_t *& _begin, const int8_t * _end)
{
	auto _begin_ptr = static_cast<int8_t*>(_begin);
	auto _end_ptr = static_cast<const int8_t*>(_end);

	// Must have at least 4 bytes
	if (_end_ptr - _begin_ptr < 4) {
		throw exception::encoding_error(BIA_EM_NOT_ENOUGH_SPACE);
	}

	memcpy(_begin, &_char, 4);
	_begin = _begin_ptr + 4;
}

code_point utf32::next(const int8_t *& _begin, const int8_t * _end)
{
	auto _begin_ptr = static_cast<const int8_t*>(_begin);
	auto _end_ptr = static_cast<const int8_t*>(_end);

	// Must have at least 4 bytes
	if (_end_ptr - _begin_ptr < 4) {
		throw exception::encoding_error(BIA_EM_INVALID_ENCODING);
	}

	code_point _char = 0;
	
	memcpy(&_char, _begin, 4);
	_begin = _begin_ptr + 4;

	return _char;
}

}
}