#pragma once

#include <string>

#include "biaHash.h"


namespace bia
{
namespace machine
{

struct BiaKeyToken
{
	const char * pcString;	/**	Defines the name.	*/
	unsigned char ucLength;	/**	Defines the length of the name.	*/
	unsigned int unHash32;	/**	Defines the name as a hash.	*/
	unsigned long long unHash64;	/**	Defines the name as a hash.	*/
};

class BiaKey
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_token	Defines the key token.
	*/
	inline BiaKey(const BiaKeyToken & p_token) : m_stString(p_token.pcString, static_cast<size_t>(p_token.ucLength))
	{
		m_unHash32 = p_token.unHash32;
		m_unHash64 = p_token.unHash64;
	}
	/**
	 * Constructor.
	 *
	 * @param	p_stStirng	Defines the name.
	*/
	inline BiaKey(std::string p_stString) : m_stString(std::move(p_stString))
	{
		m_unHash32 = utility::Hash32(m_stString.data(), static_cast<unsigned int>(m_stString.length()));
		m_unHash64 = utility::Hash64(m_stString.data(), static_cast<unsigned long long>(m_stString.length()));
	}
	inline bool operator==(const BiaKey & p_right) const
	{
		return m_unHash32 == p_right.m_unHash32 &&
			m_unHash64 == p_right.m_unHash64 &&
			m_stString == p_right.m_stString;
	}
	inline bool operator==(const BiaKeyToken & p_right) const
	{
		return m_unHash32 == p_right.unHash32 &&
			m_unHash64 == p_right.unHash64 &&
			static_cast<size_t>(p_right.ucLength) == m_stString.length() &&
			memcmp(m_stString.data(), p_right.pcString, static_cast<size_t>(p_right.ucLength)) == 0;
	}

private:
	friend utility::BiaHasher<unsigned int>;
	friend utility::BiaHasher<unsigned long long>;

	std::string m_stString;	/**	Defines the name.	*/

	unsigned int m_unHash32;	/**	Defines the name as a hash.	*/
	unsigned long long m_unHash64;	/**	Defines the name as a hash.	*/
};

}
}