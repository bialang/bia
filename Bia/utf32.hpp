#pragma once

#include "utf.hpp"

namespace bia
{
namespace encoding
{

class utf32 : public utf
{
public:
	virtual void encode(code_point _char, void *& _begin, const void * _end) override;
	virtual code_point decode(const void *& _begin, const void * _end) override;
};

}
}