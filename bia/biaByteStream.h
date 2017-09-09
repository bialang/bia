#pragma once

#include <memory>

#include "biaGlobal.h"
#include "biaException.h"


namespace bia
{
namespace stream
{

struct BiaByteStream
{
	/**
	 * Constructor.
	 *
	 * @remarks	The specified buffer has to be valid as long as this object is being used.
	 *
	 * @param	p_pBegin	Defines the beginning.
	 * @param	p_pEnd	Defines the end.
	*/
	inline BiaByteStream(const void * p_pBegin, const void * p_pEnd)
	{
		pcByteCode = static_cast<const unsigned char*>(p_pBegin);
		pcCursor = pcByteCode;
		pcByteCodeEnd = static_cast<const unsigned char*>(p_pEnd);
	}
	/**
	 * Constructor.
	 *
	 * @remarks	The specified buffer has to be valid as long as this object is being used.
	 *
	 * @param	p_pBuffer	Defines the buffer.
	 * @param	p_iSize	Defines the size of the buffer.
	*/
	inline BiaByteStream(const void * p_pBuffer, size_t p_iSize)
	{
		pcByteCode = static_cast<const unsigned char*>(p_pBuffer);
		pcCursor = pcByteCode;
		pcByteCodeEnd = pcByteCode + p_iSize;
	}
	/**
	 * Seeks the specified position.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   p_llPosition
	 *
	 * @return  true if it succeeded, otherwise false.
	*/
	inline bool SeekRead(long long p_llPosition)
	{
		if (p_llPosition <= pcByteCodeEnd - pcByteCode)
		{
			pcCursor = pcByteCode + p_llPosition;

			return true;
		}

		return false;
	}
	/**
	 * Checks if reading is still valid.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @return  true if reading is valid, otherwise false.
	*/
	template<intptr_t N>
	inline bool GoodToRead() const
	{
		return pcByteCodeEnd - pcCursor >= N;
	}
	/**
	 * Reads the type out of the byte stream.
	 *
	 * @remarks	Read() does not check whether enough space is available to read or not.
	 *
	 * @since	1.21.57.340
	 * @date	11-Jul-17
	 *
	 * @return  The read type.
	*/
	template<typename T>
	inline T Read()
	{
		T value = T();

		memcpy(&value, pcCursor, sizeof(T));
		pcCursor += sizeof(T);

		return value;
	}
	/**
	 * Reads a buffer.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   [out]	p_pBuffer	Defines the output buffer.
	 * @param	p_iSize	Defines the amount of bytes that should be read.
	 *
	 * @return  true if it succeeded, otherwise false.
	*/
	inline bool Read(void * p_pBuffer, size_t p_iSize)
	{
		if (pcByteCodeEnd - pcCursor >= static_cast<long long>(p_iSize))
		{
			memcpy(p_pBuffer, pcCursor, p_iSize);
			pcCursor += p_iSize;

			return true;
		}
		
		return false;
	}
	/**
	 * Returns the current position.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @return  The current position.
	*/
	inline long long TellRead() const
	{
		return pcCursor - pcByteCode;
	}

	const unsigned char * pcByteCode;	/**	Defines the beginning of the byte code.	*/
	const unsigned char * pcCursor;	/**	Defines the current position in the byte code.	*/
	const unsigned char * pcByteCodeEnd;	/**	Defines the end of the byte code.	*/
};

}
}