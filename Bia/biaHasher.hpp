#pragma once

#include <cstring>


namespace bia
{
namespace utility
{

template<typename>
struct BiaHasher
{
};

inline unsigned int Hash(const char * p_pcBuffer, unsigned int p_unLength)
{
	constexpr auto m = 0x5bd1e995u;
	auto unHash = 0xc70f6907u ^ p_unLength;

	while (p_unLength >= 4)
	{
		auto k = 0u;

		memcpy(&k, p_pcBuffer, 4);

		k *= m;
		k ^= k >> 24;
		k *= m;

		unHash *= m;
		unHash ^= k;

		p_pcBuffer += 4;
		p_unLength -= 4;
	}

	switch (p_unLength)
	{
	case 3:
		unHash ^= static_cast<unsigned char>(p_pcBuffer[2]) << 16;
	case 2:
		unHash ^= static_cast<unsigned char>(p_pcBuffer[1]) << 8;
	case 1:
		unHash ^= static_cast<unsigned char>(p_pcBuffer[0]);
		unHash *= m;
	};

	unHash ^= unHash >> 13;
	unHash *= m;
	unHash ^= unHash >> 15;

	return unHash;
}

inline unsigned long long ShiftMix(unsigned long long p_ullValue)
{
	return p_ullValue ^ (p_ullValue >> 47);
}

inline unsigned long long Hash(const char * p_pcBuffer, unsigned long long p_ullLength)
{
	constexpr auto m = (0xc6a4a793ull << 32) + 0x5bd1e995ull;
	const auto pcEnd = p_pcBuffer + (p_ullLength & ~0x7);
	auto ullHash = 0xc70f6907ull ^ p_ullLength * m;

	while (p_pcBuffer < pcEnd)
	{
		auto ullTmp = 0ull;

		memcpy(&ullTmp, p_pcBuffer, 8);
		p_pcBuffer += 8;

		ullHash ^= ShiftMix(ullTmp * m) * m;
		ullHash *= m;
	}

	p_ullLength &= 0x7;

	if (p_ullLength)
	{
		auto ullTmp = 0ull;

		while (p_ullLength-- > 0)
			ullTmp = (ullTmp << 8) + static_cast<unsigned char>(pcEnd[p_ullLength]);

		ullHash ^= ullTmp;
		ullHash *= m;
	}

	ullHash = ShiftMix(ullHash) * m;
	ullHash = ShiftMix(ullHash);

	return ullHash;
}

}
}