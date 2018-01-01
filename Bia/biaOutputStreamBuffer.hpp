#pragma once

#include <memory>

#include "biaOutputStream.hpp"


namespace bia
{
namespace stream
{

class BiaOutputStreamBuffer : public BiaOutputStream
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_iReserve	(Optional)	Defines the initial reserved size.
	*/
	BiaOutputStreamBuffer(size_t p_iReserve = 0);

	/**
	 * @see	BiaOutputStream::SetPosition().
	*/
	virtual void SetPosition(long long p_llPosition) override;
	/**
	 * @see	BiaOutputStream::Move().
	*/
	virtual void Move(long long p_llDestination, long long p_llSource, long long p_llSize) override;
	/**
	 * @see	BiaOutputStream::GetPosition().
	*/
	virtual long long GetPosition() const override;
	/**
	 * @see	BiaOutputStream::GetBuffer().
	*/
	virtual std::pair<const uint8_t*, size_t> GetBuffer() const override;

protected:
	virtual void Prepare(size_t p_iAdditonalSize) override;
	virtual void Write(uint64_t p_ullValue) override;
	virtual void Write(uint32_t p_unValue) override;
	virtual void Write(uint16_t p_usValue) override;
	virtual void Write(uint8_t p_ucValue) override;

private:
	std::unique_ptr<uint8_t[]> m_pucBuffer;

	size_t m_iLimit;
	size_t m_iSize;
};
	
}
}