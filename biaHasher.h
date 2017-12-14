#pragma once

#include "biaHash.h"
#include "biaKey.h"


namespace bia
{
namespace utility
{

template<>
struct BiaHasher<unsigned int>
{
	inline unsigned int operator()(const machine::BiaKey & p_key) const
	{
		return p_key.m_unHash32;
	}
};

template<>
struct BiaHasher<unsigned long long>
{
	inline unsigned long long operator()(const machine::BiaKey & p_key) const
	{
		return p_key.m_unHash64;
	}
};

typedef BiaHasher<size_t> bia_hasher;

}
}