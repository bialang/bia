#pragma once

#include <cstdint>
#include <mpir/mpir.h>
#include <type_traits>
#include <cstdlib>
#include <algorithm>
#include <cstdio>

#include "config.hpp"
#include "max.hpp"
#include "buffer_builder.hpp"
#include "exception.hpp"


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
	BIA_EXPORT big_int(const char * _value, int _base = 10);
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
	 * Prints the big integer to a file.
	 *
	 * @since 3.69.144.799
	 * @date 5-Dec-18
	 *
	 * @todo Exception handling.
	*/
	BIA_EXPORT void print(FILE * _output, int _base = 10) const;
	BIA_EXPORT void to_string(utility::buffer_builder & _destination, int _base = 10) const;
	BIA_EXPORT void set(const big_int & _value);
	void set(double _value) noexcept
	{
		set(static_cast<int64_t>(_value));
	}
	BIA_EXPORT void set(const char * _value, int _base = 10);
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
	 * @param _value The signed value.
	*/
	template<typename Type>
	typename std::enable_if<std::is_signed<Type>::value>::type set(Type _value) noexcept
	{
		auto _this = reinterpret_cast<type*>(_buffer);
		auto _unsigned = _value < 0 ? negate_cast<uint64_t>(_value) : expand_cast<uint64_t>(_value);
		constexpr auto _needed = (sizeof(Type) * 8 + GMP_NUMB_BITS - 1) / GMP_NUMB_BITS;

		for (_this->_mp_size = 0; _this->_mp_size < _needed && _unsigned; ++_this->_mp_size) {
			_this->_mp_d[_this->_mp_size] = _unsigned & GMP_NUMB_MASK;
			_unsigned >>= GMP_NUMB_BITS;
		}

		// Apply sign
		if (_value < 0) {
			_this->_mp_size = -_this->_mp_size;
		}
	}
	BIA_EXPORT void add(const big_int & _right);
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value>::type add(Type _right)
	{
		big_int_add(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), _right);
	}
	BIA_EXPORT void add(const big_int & _right, big_int & _result) const;
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value>::type add(Type _right, big_int & _result) const
	{
		big_int_add(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), _right);
	}
	BIA_EXPORT void subtract(const big_int & _right);
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value>::type subtract(Type _right)
	{
		big_int_sub(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), _right);
	}
	BIA_EXPORT void subtract(const big_int & _right, big_int & _result) const;
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value>::type subtract(Type _right, big_int & _result) const
	{
		big_int_sub(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), _right);
	}
	BIA_EXPORT void multiply(const big_int & _right);
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value>::type multiply(Type _right)
	{
		big_int_mul(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), _right);
	}
	BIA_EXPORT void multiply(const big_int & _right, big_int & _result) const;
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value>::type multiply(Type _right, big_int & _result) const
	{
		big_int_mul(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), _right);
	}
	BIA_EXPORT void divide(const big_int & _right);
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value>::type divide(Type _right)
	{
		big_int_div(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), _right);
	}
	BIA_EXPORT void divide(const big_int & _right, big_int & _result) const;
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value>::type divide(Type _right, big_int & _result) const
	{
		big_int_div(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), _right);
	}
	BIA_EXPORT void modulo(const big_int & _right);
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value>::type modulo(Type _right)
	{
		big_int_mod(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), _right);
	}
	BIA_EXPORT void modulo(const big_int & _right, big_int & _result) const;
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value>::type modulo(Type _right, big_int & _result) const
	{
		big_int_mod(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), _right);
	}
	BIA_EXPORT void power(int32_t _exponent);
	BIA_EXPORT void power(const big_int & _exponent);
	BIA_EXPORT void power(int32_t _exponent, big_int & _result) const;
	BIA_EXPORT void power(const big_int & _exponent, big_int & _result) const;
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
	BIA_EXPORT bool is_zero() const noexcept;
	BIA_EXPORT int compare(const big_int & _right) const;
	/**
	 * Casts the big int to a native int64.
	 *
	 * @remarks If the big int is too large, the result will be truncated.
	 *
	 * @since 3.69.145.800
	 * @date 22-Dec-18
	 *
	 * @return The int value.
	*/
	BIA_EXPORT int64_t cast_int() const noexcept;
	/**
	 * Casts the big int to a native int64.
	 *
	 * @since 3.69.145.800
	 * @date 22-Dec-18
	 *
	 * @param exception::overflow_error If the big int does not fit into a native int.
	 *
	 * @return The int value.
	*/
	BIA_EXPORT int64_t to_int() const;
	/**
	 * Converts the big int to a double value.
	 *
	 * @since 3.69.145.800
	 * @date 22-Dec-18
	 *
	 * @return The double value.
	*/
	BIA_EXPORT double cast_double() const noexcept;
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

	BIA_EXPORT void reset() noexcept;
	template<typename Destination, typename Source, typename Right>
	static void big_int_add(Destination _destination, Source _source, Right _right)
	{
		if (sizeof(_right) <= sizeof(mpir_ui)) {
			if (_right < 0) {
				mpz_sub_ui(_destination, _source, negate_cast<mpir_ui>(_right));
			} else {
				mpz_add_ui(_destination, _source, expand_cast<mpir_ui>(_right));
			}
		} else {
			big_int _tmp(expand_cast<int64_t>(_right));

			mpz_add(_destination, _source, reinterpret_cast<const type*>(_tmp._buffer));
		}
	}
	template<typename Destination, typename Source, typename Right>
	static void big_int_sub(Destination _destination, Source _source, Right _right)
	{
		if (sizeof(_right) <= sizeof(mpir_ui)) {
			if (_right < 0) {
				mpz_add_ui(_destination, _source, negate_cast<mpir_ui>(_right));
			} else {
				mpz_sub_ui(_destination, _source, expand_cast<mpir_ui>(_right));
			}
		} else {
			big_int _tmp(expand_cast<int64_t>(_right));

			mpz_sub(_destination, _source, reinterpret_cast<const type*>(_tmp._buffer));
		}
	}
	template<typename Destination, typename Source, typename Right>
	static void big_int_mul(Destination _destination, Source _source, Right _right)
	{
		if (sizeof(_right) <= sizeof(mpir_si)) {
			mpz_mul_si(_destination, _source, expand_cast<mpir_si>(_right));
		} else {
			big_int _tmp(expand_cast<int64_t>(_right));

			mpz_mul(_destination, _source, reinterpret_cast<const type*>(_tmp._buffer));
		}
	}
	template<typename Destination, typename Source, typename Right>
	static void big_int_div(Destination _destination, Source _source, Right _right)
	{
		if (_right == 0) {
			throw exception::zero_division_error(BIA_EM_DIVISION_BY_ZERO);
		}

		if (sizeof(_right) <= sizeof(mpir_ui)) {
			if (_right < 0) {
				mpz_tdiv_q_ui(_destination, _source, negate_cast<mpir_ui>(_right));
				mpz_neg(_destination, _destination);
			} else {
				mpz_tdiv_q_ui(_destination, _source, expand_cast<mpir_ui>(_right));
			}
		} else {
			big_int _tmp(expand_cast<int64_t>(_right));

			mpz_tdiv_q(_destination, _source, reinterpret_cast<const type*>(_tmp._buffer));
		}
	}
	template<typename Destination, typename Source, typename Right>
	static void big_int_mod(Destination _destination, Source _source, Right _right)
	{
		if (_right == 0) {
			throw exception::zero_division_error(BIA_EM_DIVISION_BY_ZERO);
		}

		if (sizeof(_right) <= sizeof(mpir_ui)) {
			if (_right < 0) {
				auto _result = _right + mpz_fdiv_r_ui(_destination, _source, negate_cast<mpir_ui>(_right));

				mpz_set_si(_destination, _result);
			} else {
				mpz_fdiv_r_ui(_destination, _source, expand_cast<mpir_ui>(_right));
			}
		} else {
			big_int _tmp(expand_cast<int64_t>(_right));

			mpz_fdiv_r(_destination, _source, reinterpret_cast<const type*>(_tmp._buffer));
		}
	}
	/**
	 * Casts @a _value to @a To_type.
	 *
	 * @since 3.69.145.800
	 * @date 22-Dec-18
	 *
	 * @tparam To_type The desired type.
	 * @tparam Type The actual type. Must meet: sizeof(Type) <= sizeof(To_type)
	 *
	 * @param _value The value that should be casted.
	 *
	 * @return The casted value.
	*/
	template<typename To_type, typename Type>
	static typename std::enable_if<std::is_unsigned<To_type>::value || std::is_signed<Type>::value, To_type>::type expand_cast(Type _value) noexcept
	{
		return static_cast<To_type>(_value);
	}
	/**
	 * Casts @a _value to @a To_type.
	 *
	 * @since 3.69.145.800
	 * @date 22-Dec-18
	 *
	 * @tparam To_type The desired type.
	 * @tparam Type The actual type. Must meet: sizeof(Type) <= sizeof(To_type)
	 *
	 * @param _value The value that should be casted. Must be negative.
	 *
	 * @return The casted positive value.
	*/
	template<typename To_type, typename Type>
	static typename std::enable_if<std::is_unsigned<To_type>::value && std::is_signed<Type>::value, To_type>::type negate_cast(Type _value) noexcept
	{
		return static_cast<To_type>(-static_cast<typename std::make_signed<To_type>::type>(_value));
	}
};

}
}