#pragma once

#include "encoder.hpp"


namespace bia
{
namespace encoding
{

class utf8 : public encoder
{
public:
	virtual void append(code_point _char, int8_t *& _begin, const int8_t * _end) override;
	virtual bool has_next(const int8_t * _begin, const int8_t * _end) noexcept override;
	virtual code_point next(const int8_t *& _begin, const int8_t * _end) override;
};

}
}