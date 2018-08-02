#pragma once

#include "encoder.hpp"
#include "exception.hpp"


namespace bia
{
namespace encoding
{

class ascii : public encoder
{
public:
	virtual void append(code_point _char, int8_t *& _begin, const int8_t * _end) override
	{
		if (_begin >= _end) {
			throw exception::encoding_error(BIA_EM_NOT_ENOUGH_SPACE);
		}

		*_begin++ = _char & 0x7f;
	}
	virtual bool has_next(const int8_t * _begin, const int8_t * _end) noexcept override
	{
		return _begin < _end;
	}
	virtual code_point next(const int8_t *& _begin, const int8_t * _end) override
	{
		if (_begin >= _end) {
			throw exception::encoding_error(BIA_EM_NOT_ENOUGH_SPACE);
		} else if (*_begin & 0x80) {
			throw exception::encoding_error(BIA_EM_INVALID_ASCII);
		}

		return *_begin++;
	}
};

}
}