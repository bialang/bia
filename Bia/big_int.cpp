#include "big_int.hpp"

#include <cstring>


namespace bia
{
namespace dependency
{

big_int::big_int(int64_t _value) noexcept : _buffer{}
{
	reset();

	// Set big int
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
	mpz_clear(reinterpret_cast<type*>(_buffer));
}

void big_int::reset() noexcept
{
	auto _ptr = reinterpret_cast<type*>(_buffer);

	_ptr->_mp_alloc = reserved_space / sizeof(*type::_mp_d);
	_ptr->_mp_d = reinterpret_cast<decltype(type::_mp_d)>(_ptr + 1);
}

}
}