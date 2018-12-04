#pragma once

#include <mpir/mpir.h>
#include <type_traits>
#include <cstdint>
#include <cstdlib>
#include <algorithm>

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
	/**
	 * Converts the signed C++ integral to a big integer.
	 *
	 * @warning The underlying big int buffer must be large enough to hold the data.
	 *
	 * @since 3.68.140.790
	 * @date 20-Oct-18
	 *
	 * @tparam Type The signed C++ integral.
	 *
	 * @param _signed The signed value.
	*/
	template<typename Type>
	void set(Type _signed) noexcept
	{
		auto _int = reinterpret_cast<type*>(_buffer);
		auto _unsigned = abs(_signed);
		constexpr auto _needed = (sizeof(Type) * 8 + GMP_NUMB_BITS - 1) / GMP_NUMB_BITS;

		for (_int->_mp_size = 0; _int->_mp_size < _needed && _unsigned; ++_int->_mp_size) {
			_int->_mp_d[_int->_mp_size] = _unsigned & GMP_NUMB_MASK;
			_unsigned >>= GMP_NUMB_BITS;
		}

		// Apply sign
		if (_signed < 0) {
			_int->_mp_size = -_int->_mp_size;
		}
	}
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
	/**
	 * Converts the big integer to a signed C++ integral.
	 *
	 * @remarks If the type can't hold all the data, only the least significant bits will be converted.
	 *
	 * @since 3.68.140.790
	 * @date 20-Oct-18
	 *
	 * @tparam Type The signed C++ integral.
	 *
	 * @return The converted value.
	*/
	template<typename Type>
	Type convert() const noexcept
	{
		Type _converted = 0;
		auto _value = reinterpret_cast<type*>(_buffer);
		auto _needed = std::min<int>((sizeof(Type) * 8 + GMP_NUMB_BITS - 1) / GMP_NUMB_BITS, abs(_value->_mp_size));

		while (_needed--) {
			_converted = _converted << GMP_NUMB_BITS | _value->_mp_d[_needed] & GMP_NUMB_MASK;
		}

		return _value->_mp_size < 0 ? -_converted : _converted;
	}

private:
	int8_t _buffer[sizeof(type) + reserved_space];

	void reset() noexcept;
};

}
}