#pragma once

#include "config.hpp"
#include "encoder.hpp"


namespace bia
{
namespace encoding
{

class utf8 : public encoder
{
public:
	BIA_EXPORT virtual void append(code_point _char, int8_t *& _begin, const int8_t * _end) override;
	BIA_EXPORT virtual bool has_next(const int8_t * _begin, const int8_t * _end) noexcept override;
	BIA_EXPORT virtual code_point next(const int8_t *& _begin, const int8_t * _end) override;
};

}
}