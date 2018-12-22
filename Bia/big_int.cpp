#include "big_int.hpp"
#include "exception.hpp"

#include <cstring>


namespace bia
{
namespace dependency
{

big_int::big_int() noexcept : _buffer{}
{
	reset();
}

big_int::big_int(int32_t _value) noexcept : big_int()
{
	set(_value);
}

big_int::big_int(int64_t _value) noexcept : big_int()
{
	set(_value);
}

big_int::big_int(const char * _value, int _base) : big_int()
{
	set(_value, _base);
}

big_int::big_int(const big_int & _copy)
{
	if (reinterpret_cast<const type*>(_copy._buffer)->_mp_alloc == reserved_space / sizeof(*type::_mp_d)) {
		std::memcpy(_buffer, _copy._buffer, sizeof(_buffer));

		auto _ptr = reinterpret_cast<type*>(_buffer);

		_ptr->_mp_d = reinterpret_cast<decltype(type::_mp_d)>(_ptr + 1);
	} else {
		mpz_init_set(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_copy._buffer));
	}
}

big_int::big_int(big_int && _move) noexcept
{
	std::memcpy(_buffer, _move._buffer, sizeof(_buffer));

	auto _ptr = reinterpret_cast<type*>(_buffer);

	_ptr->_mp_d = reinterpret_cast<decltype(type::_mp_d)>(_ptr + 1);

	// Reset move big int
	std::memset(_move._buffer, 0, sizeof(_buffer));

	_move.reset();
}

big_int::~big_int()
{
	auto _ptr = reinterpret_cast<type*>(_buffer);

	if (_ptr->_mp_alloc != reserved_space / sizeof(*type::_mp_d)) {
		mpz_clear(reinterpret_cast<type*>(_buffer));
	}
}

void big_int::print(FILE * _output, int _base) const
{
	if (!mpz_out_str(_output, _base, reinterpret_cast<const type*>(_buffer))) {
		BIA_IMPLEMENTATION_ERROR;
	}
}

void big_int::to_string(utility::buffer_builder & _destination, int _base) const
{
	_destination.resize(mpz_sizeinbase(reinterpret_cast<const type*>(_buffer), _base));

	mpz_get_str(_destination.buffer<char>(), _base, reinterpret_cast<const type*>(_buffer));

	// Resize
	if (!_destination.buffer<char>()[_destination.size() - 1]) {
		_destination.resize(_destination.size() - 1);
	}
}

void big_int::set(const big_int & _value)
{
	mpz_set(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_value._buffer));
}

void big_int::set(const char * _value, int _base)
{
	if (mpz_set_str(reinterpret_cast<type*>(_buffer), _value, _base)) {
		BIA_NOT_IMPLEMENTED;
	}
}

void big_int::reset() noexcept
{
	auto _ptr = reinterpret_cast<type*>(_buffer);

	_ptr->_mp_alloc = reserved_space / sizeof(*type::_mp_d);
	_ptr->_mp_d = reinterpret_cast<decltype(type::_mp_d)>(_ptr + 1);
}

void big_int::add(const big_int & _right)
{
	mpz_add(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::add(const big_int & _right, big_int & _result) const
{
	mpz_add(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::subtract(const big_int & _right)
{
	mpz_sub(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::subtract(const big_int & _right, big_int & _result) const
{
	mpz_sub(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::multiply(const big_int & _right)
{
	mpz_mul(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::multiply(const big_int & _right, big_int & _result) const
{
	mpz_mul(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::divide(const big_int & _right)
{
	mpz_div(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::divide(const big_int & _right, big_int & _result) const
{
	mpz_div(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::modulo(const big_int & _right)
{
	mpz_mod(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::modulo(const big_int & _right, big_int & _result) const
{
	mpz_mod(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::power(int32_t _exponent)
{
	static_assert(sizeof(_exponent) <= sizeof(mpir_ui), "Exponent size mismatch.");

	if (_exponent < 0) {
		BIA_NOT_IMPLEMENTED;
	}

	mpz_pow_ui(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), _exponent);
}

void big_int::power(const big_int & _exponent)
{
	BIA_NOT_IMPLEMENTED;
}

void big_int::power(int32_t _exponent, big_int & _result) const
{
	if (_exponent < 0) {
		_result.set(0);
	} else {
		mpz_pow_ui(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), _exponent);
	}
}

void big_int::power(const big_int & _exponent, big_int & _result) const
{
	BIA_NOT_IMPLEMENTED;
}

void big_int::negate()
{
	mpz_neg(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer));
}

void big_int::negate(big_int & _result) const
{
	mpz_neg(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer));
}

void big_int::bitwise_and(const big_int & _right)
{
	mpz_and(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::bitwise_and(const big_int & _right, big_int & _result) const
{
	mpz_and(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::bitwise_or(const big_int & _right)
{
	mpz_ior(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::bitwise_or(const big_int & _right, big_int & _result) const
{
	mpz_ior(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::bitwise_xor(const big_int & _right)
{
	mpz_xor(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::bitwise_xor(const big_int & _right, big_int & _result) const
{
	mpz_xor(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer), reinterpret_cast<const type*>(_right._buffer));
}

void big_int::complement()
{
	mpz_com(reinterpret_cast<type*>(_buffer), reinterpret_cast<const type*>(_buffer));
}

void big_int::complement(big_int & _result) const
{
	mpz_com(reinterpret_cast<type*>(_result._buffer), reinterpret_cast<const type*>(_buffer));
}

void big_int::left_shift(unsigned int _count)
{
	BIA_NOT_IMPLEMENTED;
}

void big_int::left_shift(unsigned int _count, big_int & _result) const
{
	BIA_NOT_IMPLEMENTED;
}

void big_int::arithmetic_right_shift(unsigned int _count)
{
	BIA_NOT_IMPLEMENTED;
}

void big_int::arithmetic_right_shift(unsigned int _count, big_int & _result) const
{
	BIA_NOT_IMPLEMENTED;
}

void big_int::logical_right_shift(unsigned int _count)
{
	BIA_NOT_IMPLEMENTED;
}

void big_int::logical_right_shift(unsigned int _count, big_int & _result) const
{
	BIA_NOT_IMPLEMENTED;
}

bool big_int::is_zero() const noexcept
{
	return !reinterpret_cast<const type*>(_buffer)->_mp_size;
}

bool big_int::fits_int() const noexcept
{
	auto _value = reinterpret_cast<const type*>(_buffer);
	auto _size = abs(_value->_mp_size);
	constexpr auto _int_size = (sizeof(int64_t) * 8 + GMP_NUMB_BITS - 1) / GMP_NUMB_BITS;

	// Fits or does not
	if (_size != _int_size) {
		return _size < _int_size;
	}

	// Check limits
	BIA_NOT_IMPLEMENTED;
}

int64_t big_int::cast_int() const noexcept
{
	int64_t _converted = 0;
	auto _value = reinterpret_cast<const type*>(_buffer);
	auto _needed = std::min<int>((sizeof(int64_t) * 8 + GMP_NUMB_BITS - 1) / GMP_NUMB_BITS, abs(_value->_mp_size));

	while (_needed--) {
		_converted = _converted << GMP_NUMB_BITS | _value->_mp_d[_needed] & GMP_NUMB_MASK;
	}

	return _value->_mp_size < 0 ? -_converted : _converted;
}

int64_t big_int::to_int() const
{
	uint64_t _converted = 0;
	auto _value = reinterpret_cast<const type*>(_buffer);
	constexpr auto _needed = (sizeof(int64_t) * 8 + GMP_NUMB_BITS - 1) / GMP_NUMB_BITS;
	auto _size = _value->_mp_size;
	
	if (_size == 0) {
		return 0;
	} else if (_size > 0) {
		if (_size > _needed) {
			throw exception::overflow_error(BIA_EM_INT_OVERFLOW);
		}

		while (_size--) {
			_converted = _converted << GMP_NUMB_BITS | _value->_mp_d[_size] & GMP_NUMB_MASK;
		}

		if (_converted > static_cast<uint64_t>(std::numeric_limits<int64_t>::max())) {
			throw exception::overflow_error(BIA_EM_INT_OVERFLOW);
		}

		return static_cast<int64_t>(_converted);
	} else {
		_size = -_size;

		if (_size > _needed) {
			throw exception::overflow_error(BIA_EM_INT_UNDERFLOW);
		}

		while (_size--) {
			_converted = _converted << GMP_NUMB_BITS | _value->_mp_d[_size] & GMP_NUMB_MASK;
		}

		if (_converted > static_cast<uint64_t>(std::numeric_limits<int64_t>::min())) {
			throw exception::overflow_error(BIA_EM_INT_UNDERFLOW);
		}

		return -static_cast<int64_t>(_converted);
	}
}

double big_int::cast_double() const noexcept
{
	try {
		return mpz_get_d(reinterpret_cast<const type*>(_buffer));
	} catch (...) {
	}

	return std::numeric_limits<double>::quiet_NaN();
}

double big_int::to_double() const
{
	return mpz_get_d(reinterpret_cast<const type*>(_buffer));
}

}
}