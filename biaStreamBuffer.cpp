#include "biaStreamBuffer.h"

#include <cstring>


namespace bia
{
namespace stream
{

BiaStreamBuffer::BiaStreamBuffer(size_t p_iReserve)
{
	m_iSize = 0;

	if (m_iLimit = p_iReserve)
		m_pucBuffer.reset(new uint8_t[m_iLimit]);
}

std::pair<const uint8_t*, size_t> BiaStreamBuffer::GetBuffer() const
{
	return  { m_pucBuffer.get(), m_iSize };
}

void BiaStreamBuffer::Prepare(size_t p_iAdditonalSize)
{
	if (m_iLimit < p_iAdditonalSize + m_iSize)
	{
		m_iLimit = (m_iLimit + p_iAdditonalSize) * 2;

		auto pucNew = new uint8_t[m_iLimit];

		memcpy(pucNew, m_pucBuffer.get(), m_iSize);

		m_pucBuffer.reset(pucNew);
	}
}

void BiaStreamBuffer::Write(uint64_t p_ullValue)
{
	memcpy(m_pucBuffer.get() + m_iSize, &p_ullValue, 8);

	m_iSize += 8;
}

void BiaStreamBuffer::Write(uint32_t p_unValue)
{
	memcpy(m_pucBuffer.get() + m_iSize, &p_unValue, 4);

	m_iSize += 4;
}

void BiaStreamBuffer::Write(uint16_t p_usValue)
{
	memcpy(m_pucBuffer.get() + m_iSize, &p_usValue, 2);

	m_iSize += 2;
}

void BiaStreamBuffer::Write(uint8_t p_ucValue)
{
	m_pucBuffer[m_iSize++] = p_ucValue;
}

}
}