#pragma once

#include "utf.hpp"


namespace bia
{
namespace encoding
{

class utf8 : public utf
{
public:
	virtual void append(code_point _char, int8_t *& _begin, const int8_t * _end) override;
	virtual code_point next(const int8_t *& _begin, const int8_t * _end) override;
};

}
}