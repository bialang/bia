#pragma once

#include <mpir/mpir.h>

#include "big_int.hpp"


namespace bia
{
namespace dependency
{

template<typename Destination, typename Source, typename Right>
inline void big_int_add(Destination _destination, Source _source, Right _right)
{
	if (sizeof(_right) <= sizeof(mpir_ui)) {
		if (_right < 0) {
			mpz_sub_ui(_destination, _source, static_cast<mpir_ui>(-_right));
		} else {
			mpz_add_ui(_destination, _source, -_right);
		}
	} else {
		big_int _tmp(_right);

		mpz_add(_destination, _source, reinterpret_cast<const big_int::type*>(_tmp._buffer));
	}
}

template<typename Destination, typename Source, typename Right>
inline void big_int_sub(Destination _destination, Source _source, Right _right)
{
	if (sizeof(_right) <= sizeof(mpir_ui)) {
		if (_right < 0) {
			mpz_add_ui(_destination, _source, static_cast<mpir_ui>(-_right));
		} else {
			mpz_sub_ui(_destination, _source, -_right);
		}
	} else {
		big_int _tmp(_right);

		mpz_sub(_destination, _source, reinterpret_cast<const big_int::type*>(_tmp._buffer));
	}
}

}
}