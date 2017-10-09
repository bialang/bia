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
	/**
	 * Reserves the specified amount of bytes.
	 *
	 * @param	p_iSize	Defines the size.
	*/
	virtual void Reserve(size_t p_iSize) = 0;
	/**
	 * Writes the specifed buffer to the stream.
	 *
	 * @param	p_pBuffer	Defines the buffer.
	 * @param	p_iSize	Defines the size of the buffer.
	*/
	virtual void Write(const void * p_pBuffer, size_t p_iSize) = 0;
	/**
	 * Commits the last retrieved buffer.
	 *
	 * @param	p_iSize	Defines the actual size written to the buffer.
	*/
	virtual void CommitBuffer(size_t p_iSize) = 0;
	/**
	 * Copies from the specified position the specified amount of bytes to the current cursor postion.
	 *
	 * @param	p_llPosition	Defines the position.
	 * @param	p_iSize	Defines the amount of bytes that should be copied.
	*/
	virtual void CopyFrom(long long p_llPosition, size_t p_iSize) = 0;
	/**
	 * Moves the cursor to the position.
	 *
	 * @param	p_llPosition	Defines the position.
	 *
	 * @return	true if it succeeds, otherwise false.
	*/
	virtual bool SeekWrite(long long p_llPosition) = 0;
	/**
	 * Tells the current position of the cursor.
	 *
	 * @return	The position of the cursor.
	*/
	virtual long long TellWrite() = 0;
	/**
	 * Readies the a buffer and returns it.
	 *
	 * @param	p_iSize	Defines the maximum intended size of the buffer.
	 *
	 * @return	The buffer.
	*/
	virtual char * GetBuffer(size_t p_iSize) = 0;
};

}
}