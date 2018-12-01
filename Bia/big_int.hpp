#pragma once

#include <mpir/mpir.h>
#include <type_traits>
#include <cstdint>

#include "config.hpp"


namespace bia
{
namespace dependency
{

class big_int
{
public:
	typedef typename std::remove_extent<mpz_t>::type type;

	constexpr static auto reserved_space = sizeof(*type::_mp_d) * 2;

	BIA_EXPORT big_int(int64_t _value = 0) noexcept;
	BIA_EXPORT big_int(const big_int & _copy);
	BIA_EXPORT big_int(big_int && _move) noexcept;
	BIA_EXPORT ~big_int();
	BIA_EXPORT void add(const big_int & _right);
	BIA_EXPORT void add(const big_int & _right, big_int & _result) const;
	BIA_EXPORT void subtract(const big_int & _right);
	BIA_EXPORT void subtract(const big_int & _right, big_int & _result) const;
	BIA_EXPORT void multiply(const big_int & _right);
	BIA_EXPORT void multiply(const big_int & _right, big_int & _result) const;
	BIA_EXPORT void divide(const big_int & _right);
	BIA_EXPORT void divide(const big_int & _right, big_int & _result) const;
	BIA_EXPORT void modulo(const big_int & _right);
	BIA_EXPORT void modulo(const big_int & _right, big_int & _result) const;
	BIA_EXPORT void negate();
	BIA_EXPORT void negate(big_int & _result) const;
	BIA_EXPORT void bitwise_and(const big_int & _right);
	BIA_EXPORT void bitwise_and(const big_int & _right, big_int & _result) const;
	BIA_EXPORT void bitwise_or(const big_int & _right);
	BIA_EXPORT void bitwise_or(const big_int & _right, big_int & _result) const;
	BIA_EXPORT void bitwise_xor(const big_int & _right);
	BIA_EXPORT void bitwise_xor(const big_int & _right, big_int & _result) const;
	BIA_EXPORT void complement();
	BIA_EXPORT void complement(big_int & _result) const;
	BIA_EXPORT void left_shift(unsigned int _count);
	BIA_EXPORT void left_shift(unsigned int _count, big_int & _result) const;
	BIA_EXPORT void arithmetic_right_shift(unsigned int _count);
	BIA_EXPORT void arithmetic_right_shift(unsigned int _count, big_int & _result) const;
	BIA_EXPORT void logical_right_shift(unsigned int _count);
	BIA_EXPORT void logical_right_shift(unsigned int _count, big_int & _result) const;

private:
	int8_t _buffer[sizeof(type) + reserved_space];

	void reset() noexcept;
};

}
}