#pragma once

#include "biaGlobal.h"
#include "biaByteStream.h"


namespace bia
{
namespace machine
{
namespace debug
{

class BiaDisassembler
{
public:
	BIA_API static void DisassembleByteCode(stream::BiaByteStream p_byteCode);
};

}
}
}