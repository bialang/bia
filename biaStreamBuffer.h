#pragma once

#include <memory>

#include "biaStream.h"
#include "biaByteStream.h"


namespace bia
{
namespace stream
{

class BiaStreamBuffer : public virtual BiaStream
{
public:
	inline BiaStreamBuffer()
	{
		m_pcCursor = nullptr;

		m_llCapacity = 0;
	}
	BiaStreamBuffer(BiaStreamBuffer&&) = delete;
	BiaStreamBuffer(const BiaStreamBuffer&) = delete;
	inline void Clear()
	{
		m_pcCursor = m_pcBufferBegin.get();
	}
	inline virtual void Reserve(size_t p_iSize) override final
	{
		if (p_iSize > m_llCapacity)
		{
			auto pcNew = new unsigned char[p_iSize];

			memcpy(pcNew, m_pcBufferBegin.get(), m_pcCursor - m_pcBufferBegin.get());

			m_llCapacity = p_iSize;
			m_pcCursor = pcNew + (m_pcCursor - m_pcBufferBegin.get());
			m_pcBufferBegin.reset(pcNew);
		}
	}
	inline virtual void Write(const void * p_pBuffer, size_t p_iSize) override final
	{
		Enlarge(p_iSize);

		memcpy(m_pcCursor, p_pBuffer, p_iSize);

		m_pcCursor += p_iSize;
	}
	inline virtual void CommitBuffer(size_t p_iSize) override final
	{
		m_pcCursor += p_iSize;
	}
	inline virtual void CopyFrom(long long p_llPosition, size_t p_iSize) override final
	{
		Enlarge(p_iSize);

		memcpy(m_pcCursor, m_pcBufferBegin.get() + p_llPosition, p_iSize);

		m_pcCursor += p_iSize;
	}
	inline virtual bool SeekWrite(long long p_llPosition) override final
	{
		if (p_llPosition < m_llCapacity)
		{
			m_pcCursor = m_pcBufferBegin.get() + p_llPosition;

			return true;
		}

		return false;
	}
	inline virtual long long TellWrite() override final
	{
		return m_pcCursor - m_pcBufferBegin.get();
	}
	inline virtual char * GetBuffer(size_t p_iSize) override final
	{
		Enlarge(p_iSize);

		return reinterpret_cast<char*>(m_pcCursor);
	}
	inline BiaByteStream GetByteStream() const
	{
		return BiaByteStream(m_pcBufferBegin.get(), m_pcCursor);
	}

protected:
	std::unique_ptr<unsigned char[]> m_pcBufferBegin;
	unsigned char * m_pcCursor;

	long long m_llCapacity;


	inline virtual void Enlarge(size_t p_iAdditionalSize)
	{
		//Resize
		if (m_llCapacity - (m_pcCursor - m_pcBufferBegin.get()) < p_iAdditionalSize)
		{
			auto llReserve = (m_llCapacity + 1) * 2;

			while (llReserve < m_llCapacity + p_iAdditionalSize)
				llReserve = llReserve * 2 + 2;

			Reserve(static_cast<size_t>(llReserve));
		}
	}
};

}
}