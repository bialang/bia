#pragma once

#include "utf.hpp"

namespace bia
{
namespace encoding
{

class utf32 : public utf
{
public:
	virtual void encode(char_type _char, void *& _begin, const void * _end) override;
	virtual char_type decode(const void *& _begin, const void * _end) override;
};

}
}