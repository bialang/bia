#pragma once

#include "biaOpCodes.h"


namespace bia
{
namespace stream
{

class BiaStream
{
public:
	virtual ~BiaStream() = default;
	virtual void Reserve(size_t p_iSize) = 0;
	virtual void Write(const void * p_pBuffer, size_t p_iSize) = 0;
	virtual void CommitBuffer(size_t p_iSize) = 0;
	virtual bool SeekWrite(long long p_llPosition) = 0;
	virtual long long TellWrite() = 0;
	virtual char * GetBuffer(size_t p_iSize) = 0;
};

}
}