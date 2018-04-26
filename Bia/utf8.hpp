#pragma once

#include "utf.hpp"


namespace bia
{
namespace encoding
{

class utf8 : public utf
{
public:
	virtual void append(char_type _char, int8_t *& _begin, const int8_t * _end) override;
	virtual char_type next(const int8_t *& _begin, const int8_t * _end) override;
};

}
}