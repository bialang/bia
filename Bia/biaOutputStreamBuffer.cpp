#include "biaOutputStreamBuffer.hpp"

#include <cstring>


namespace bia
{
namespace stream
{

BiaOutputStreamBuffer::BiaOutputStreamBuffer(size_t p_iReserve)
{
	m_iSize = 0;

	if (m_iLimit = p_iReserve)
		m_pucBuffer.reset(new uint8_t[m_iLimit]);
}

void BiaOutputStreamBuffer::SetPosition(long long p_llPosition)
{
	if (static_cast<size_t>(p_llPosition) <= m_iLimit)
		m_iSize = static_cast<size_t>(p_llPosition);
}

void BiaOutputStreamBuffer::Move(long long p_llDestination, long long p_llSource, long long p_llSize)
{
	memmove(m_pucBuffer.get() + p_llDestination, m_pucBuffer.get() + p_llSource, p_llSize);

	m_iSize -= p_llSource - p_llDestination;
}

long long BiaOutputStreamBuffer::GetPosition() const
{
	return static_cast<long long>(m_iSize);
}

std::pair<const uint8_t*, size_t> BiaOutputStreamBuffer::GetBuffer() const
{
	return  { m_pucBuffer.get(), m_iSize };
}

void BiaOutputStreamBuffer::Prepare(size_t p_iAdditonalSize)
{
	if (m_iLimit < p_iAdditonalSize + m_iSize)
	{
		m_iLimit = (m_iLimit + p_iAdditonalSize) * 2;

		auto pucNew = new uint8_t[m_iLimit];

		memcpy(pucNew, m_pucBuffer.get(), m_iSize);

		m_pucBuffer.reset(pucNew);
	}
}

void BiaOutputStreamBuffer::Write(uint64_t p_ullValue)
{
	memcpy(m_pucBuffer.get() + m_iSize, &p_ullValue, 8);

	m_iSize += 8;
}

void BiaOutputStreamBuffer::Write(uint32_t p_unValue)
{
	memcpy(m_pucBuffer.get() + m_iSize, &p_unValue, 4);

	m_iSize += 4;
}

void BiaOutputStreamBuffer::Write(uint16_t p_usValue)
{
	memcpy(m_pucBuffer.get() + m_iSize, &p_usValue, 2);

	m_iSize += 2;
}

void BiaOutputStreamBuffer::Write(uint8_t p_ucValue)
{
	m_pucBuffer[m_iSize++] = p_ucValue;
}

}
}