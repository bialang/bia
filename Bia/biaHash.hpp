#pragma once

#include <cstdint>
#include <cstring>


namespace bia
{
namespace utility
{

template<typename>
struct BiaHasher;

template<>
struct BiaHasher<uint32_t>
{
	inline uint32_t operator()(const char * p_pcBuffer, uint32_t p_unLength)
	{
		constexpr auto M = 0x5bd1e995;
		uint32_t unHash = 0xc70f6907 ^ p_unLength;

		while (p_unLength >= 4)
		{
			uint32_t k = 0;

			memcpy(&k, p_pcBuffer, 4);

			k *= M;
			k ^= k >> 24;
			k *= M;

			unHash *= M;
			unHash ^= k;

			p_pcBuffer += 4;
			p_unLength -= 4;
		}

		switch (p_unLength)
		{
		case 3:
			unHash ^= static_cast<uint8_t>(p_pcBuffer[2]) << 16;
		case 2:
			unHash ^= static_cast<uint8_t>(p_pcBuffer[1]) << 8;
		case 1:
			unHash ^= static_cast<uint8_t>(p_pcBuffer[0]);
			unHash *= M;
		};

		unHash ^= unHash >> 13;
		unHash *= M;
		unHash ^= unHash >> 15;

		return unHash;
	}
};

template<>
struct BiaHasher<uint64_t>
{
	inline uint64_t Hash64(const char * p_pcBuffer, uint64_t p_ullLength)
	{
		constexpr auto M = (0xc6a4a793ull << 32) + 0x5bd1e995;
		const auto pcEnd = p_pcBuffer + (p_ullLength & ~0x7);
		uint64_t ullHash = 0xc70f6907 ^ p_ullLength * M;

		while (p_pcBuffer < pcEnd)
		{
			uint64_t ullTmp = 0;

			memcpy(&ullTmp, p_pcBuffer, 8);
			p_pcBuffer += 8;

			ullHash ^= ShiftMix(ullTmp * M) * M;
			ullHash *= M;
		}

		p_ullLength &= 0x7;

		if (p_ullLength)
		{
			uint64_t ullTmp = 0;

			while (p_ullLength-- > 0)
				ullTmp = (ullTmp << 8) + static_cast<uint8_t>(pcEnd[p_ullLength]);

			ullHash ^= ullTmp;
			ullHash *= M;
		}

		ullHash = ShiftMix(ullHash) * M;
		ullHash = ShiftMix(ullHash);

		return ullHash;
	}

private:
	inline uint64_t ShiftMix(uint64_t p_ullValue)
	{
		return p_ullValue ^ (p_ullValue >> 47);
	}
};
}
}