#pragma once

#include <cstdint>
#include <mpir/mpir.h>
#include <type_traits>
#include <cstdlib>
#include <algorithm>

#include "config.hpp"


namespace bia
{
namespace dependency
{

/**
 * @brief A big integer.
 *
 * A big integer class. The default used underlying library is MPIR.
 *
 * @see @ref machine::memory::big_int_allocator
*/
class big_int
{
public:
	/** The base data type of the big int of the underlying big int library. */
	typedef typename std::remove_extent<mpz_t>::type type;

	/** The additional reserved space. */
	constexpr static auto reserved_space = sizeof(*type::_mp_d) * 2;

	/**
	 * Constructor. Sets the big int to 0.
	 *
	 * @since 3.69.144.799
	 * @date 5-Dec-18
	*/
	BIA_EXPORT big_int() noexcept;
	/**
	 * Constructor.
	 *
	 * @since 3.69.144.799
	 * @date 5-Dec-18
	 *
	 * @param _value The initial value.
	*/
	BIA_EXPORT big_int(int32_t _value) noexcept;
	/**
	 * Constructor.
	 *
	 * @since 3.69.144.799
	 * @date 5-Dec-18
	 *
	 * @param _value The initial value.
	*/
	BIA_EXPORT big_int(int64_t _value) noexcept;
	/**
	 * Copy-Constructor.
	 *
	 * @since 3.69.144.798
	 * @date 5-Dec-18
	 *
	 * @param _copy The big int that should be copied.
	 *
	 * @throws See machine::memory::big_int_allocator::allocate().
	*/
	BIA_EXPORT big_int(const big_int & _copy);
	/**
	 * Move-Constructor.
	 *
	 * @since 3.69.144.798
	 * @date 5-Dec-18
	 *
	 * @param [in,out] _move The big int that should be moved. This will be set to 0 after moving.
	*/
	BIA_EXPORT big_int(big_int && _move) noexcept;
	/**
	 * Destructor.
	 *
	 * @since 3.69.144.798
	 * @date 5-Dec-18
	 *
	 * @throws See machine::memory::big_int_allocator::free().
	*/
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
		auto _value = reinterpret_cast<type*>(_buffer);
		auto _unsigned = abs(_signed);
		constexpr auto _needed = (sizeof(Type) * 8 + GMP_NUMB_BITS - 1) / GMP_NUMB_BITS;

		for (_value->_mp_size = 0; _value->_mp_size < _needed && _unsigned; ++_value->_mp_size) {
			_value->_mp_d[_value->_mp_size] = _unsigned & GMP_NUMB_MASK;
			_unsigned >>= GMP_NUMB_BITS;
		}

		// Apply sign
		if (_signed < 0) {
			_value->_mp_size = -_value->_mp_size;
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
	BIA_EXPORT bool fits_int() const noexcept;
	BIA_EXPORT int64_t to_int() const noexcept;
	/**
	 * Converts the big int to a double value.
	 *
	 * @since 3.69.144.798
	 * @date 5-Dec-18
	 *
	 * @throws exception::overflow_error If the int value is too big. This depends on the hardware implementation.
	 *
	 * @return The double value.
	*/
	BIA_EXPORT double to_double() const;

private:
	/** Enough space for the underlying big int data. */
	int8_t _buffer[sizeof(type) + reserved_space];

	void reset() noexcept;
};

}
}