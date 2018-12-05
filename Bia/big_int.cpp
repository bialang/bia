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

double big_int::to_double() const
{
	return mpz_get_d(reinterpret_cast<const type*>(_buffer));
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

int64_t big_int::to_int() const noexcept
{
	int64_t _converted = 0;
	auto _value = reinterpret_cast<const type*>(_buffer);
	auto _needed = std::min<int>((sizeof(int64_t) * 8 + GMP_NUMB_BITS - 1) / GMP_NUMB_BITS, abs(_value->_mp_size));

	while (_needed--) {
		_converted = _converted << GMP_NUMB_BITS | _value->_mp_d[_needed] & GMP_NUMB_MASK;
	}

	return _value->_mp_size < 0 ? -_converted : _converted;
	/*static_assert(sizeof(int64_t) == sizeof(intmax_t), "Integer type mismatch.");

	return mpz_get_sx(reinterpret_cast<const type*>(_buffer));*/
}

}
}