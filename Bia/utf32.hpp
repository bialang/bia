#pragma once

#include "encoder.hpp"

namespace bia
{
namespace encoding
{

class utf32 : public encoder
{
public:
	virtual void append(code_point _char, int8_t *& _begin, const int8_t * _end) override;
	virtual code_point next(const int8_t *& _begin, const int8_t * _end) override;
};

}
}