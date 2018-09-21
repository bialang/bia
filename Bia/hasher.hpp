#pragma once

#include <cstdint>
#include <cstring>


namespace bia
{
namespace utility
{

template<typename Type>
class hasher;

template<>
class hasher<uint32_t>
{
public:
	static uint32_t hash(const char * _buffer, uint32_t _length) noexcept
	{
		constexpr auto M = 0x5bd1e995;
		uint32_t _hash = 0xc70f6907 ^ _length;

		while (_length >= 4) {
			uint32_t k = 0;

			memcpy(&k, _buffer, 4);

			k *= M;
			k ^= k >> 24;
			k *= M;

			_hash *= M;
			_hash ^= k;

			_buffer += 4;
			_length -= 4;
		}

		switch (_length) {
		case 3:
			_hash ^= static_cast<uint8_t>(_buffer[2]) << 16;
		case 2:
			_hash ^= static_cast<uint8_t>(_buffer[1]) << 8;
		case 1:
			_hash ^= static_cast<uint8_t>(_buffer[0]);
			_hash *= M;
		};

		_hash ^= _hash >> 13;
		_hash *= M;
		_hash ^= _hash >> 15;

		return _hash;
	}
};

template<>
class hasher<uint64_t>
{
public:
	static uint64_t hash(const char * _buffer, uint64_t _length) noexcept
	{
		constexpr auto M = (0xc6a4a793ull << 32) + 0x5bd1e995;
		const auto _end = _buffer + (_length & ~0x7);
		uint64_t _hash = 0xc70f6907 ^ _length * M;

		while (_buffer < _end) {
			uint64_t _temp = 0;

			memcpy(&_temp, _buffer, 8);
			_buffer += 8;

			_hash ^= shift_mix(_temp * M) * M;
			_hash *= M;
		}

		_length &= 0x7;

		if (_length) {
			uint64_t _temp = 0;

			while (_length-- > 0) {
				_temp = (_temp << 8) + static_cast<uint8_t>(_end[_length]);
			}

			_hash ^= _temp;
			_hash *= M;
		}

		_hash = shift_mix(_hash) * M;
		_hash = shift_mix(_hash);

		return _hash;
	}

private:
	static uint64_t shift_mix(uint64_t _value) noexcept
	{
		return _value ^ (_value >> 47);
	}
};
}
}